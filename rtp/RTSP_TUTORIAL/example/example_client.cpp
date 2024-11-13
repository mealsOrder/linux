#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#define RTP_PORT 5004
#define RTP_HEADER_SIZE 12
#define BUFFER_SIZE 4096  // 버퍼 크기 증가

struct rtp_header {
    unsigned char vpxcc;
    unsigned char mpt;
    unsigned short sequence_number;
    unsigned int timestamp;
    unsigned int ssrc;
};

void print_rtp_header(struct rtp_header *header) {
    printf("RTP Version: %d\n", header->vpxcc >> 6);
    printf("Payload Type: %d\n", header->mpt & 0x7F);
    printf("Sequence Number: %d\n", ntohs(header->sequence_number));
    printf("Timestamp: %u\n", ntohl(header->timestamp));
    printf("SSRC: %u\n", ntohl(header->ssrc));
}

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    socklen_t len;
    char buffer[BUFFER_SIZE];
    struct rtp_header rtp_hdr;

    const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) {
        std::cerr << "H.264 codec not found" << std::endl;
        return -1;
    }

    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        std::cerr << "Could not allocate video codec context" << std::endl;
        return -1;
    }

    if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
        std::cerr << "Could not open codec" << std::endl;
        return -1;
    }

    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        std::cerr << "Could not allocate AVFrame" << std::endl;
        return -1;
    }

    AVPacket *pkt = av_packet_alloc();
    if (!pkt) {
        std::cerr << "Could not allocate AVPacket" << std::endl;
        return -1;
    }

    cv::namedWindow("RTP H.264 Stream", cv::WINDOW_AUTOSIZE);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(RTP_PORT);

    sendto(sockfd, "Hello", 5, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    std::vector<uint8_t> h264_buffer;

    // 색공간 변환을 위한 SwsContext 초기화
    SwsContext *sws_ctx = nullptr;

    while (true) {
        len = sizeof(servaddr);
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);

        if (n < RTP_HEADER_SIZE) {
            printf("Received packet is too small to contain RTP header\n");
            continue;
        }

        memcpy(&rtp_hdr, buffer, RTP_HEADER_SIZE);
        print_rtp_header(&rtp_hdr);

        size_t payload_size = n - RTP_HEADER_SIZE;
        h264_buffer.insert(h264_buffer.end(), buffer + RTP_HEADER_SIZE, buffer + RTP_HEADER_SIZE + payload_size);

        // 마커 비트가 설정되면 전체 프레임을 수신한 것으로 간주
        if (rtp_hdr.mpt & 0x80) {  
            if (av_new_packet(pkt, h264_buffer.size()) < 0) {
                std::cerr << "Error initializing packet with data size" << std::endl;
                h264_buffer.clear();
                continue;
            }
            memcpy(pkt->data, h264_buffer.data(), h264_buffer.size());

            int ret = avcodec_send_packet(codec_ctx, pkt);
            if (ret < 0) {
                av_packet_unref(pkt);
                h264_buffer.clear();
                continue;
            }

            while (avcodec_receive_frame(codec_ctx, frame) >= 0) {
                // SwsContext를 한 번만 초기화하고 재사용
                if (!sws_ctx) {
                    sws_ctx = sws_getContext(
                        codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                        codec_ctx->width, codec_ctx->height, AV_PIX_FMT_BGR24,
                        SWS_BILINEAR, nullptr, nullptr, nullptr);
                }

                if (!sws_ctx) {
                    std::cerr << "Error initializing SwsContext" << std::endl;
                    break;
                }

                // FFmpeg를 통해 색공간 변환
                cv::Mat img(codec_ctx->height, codec_ctx->width, CV_8UC3);
                uint8_t *dest[1] = { img.data };
                int dest_linesize[1] = { static_cast<int>(img.step[0]) };

                sws_scale(sws_ctx, frame->data, frame->linesize, 0, codec_ctx->height, dest, dest_linesize);

                if (!img.empty()) {
                    cv::imshow("RTP H.264 Stream", img);
                } else {
                    std::cerr << "Decoded frame is empty" << std::endl;
                }

                if (cv::waitKey(1) == 'q') {
                    av_packet_free(&pkt);
                    av_frame_free(&frame);
                    avcodec_free_context(&codec_ctx);
                    close(sockfd);
                    cv::destroyAllWindows();
                    return 0;
                }
            }
            av_packet_unref(pkt);
            h264_buffer.clear();  // 프레임 처리 후 h264_buffer 초기화
        }
    }

    // 메모리 해제
    sws_freeContext(sws_ctx);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
    close(sockfd);
    cv::destroyAllWindows();

    return 0;
}
