#include "server.hpp"

// FFmpeg 라이브러리 헤더를 extern "C"로 래핑
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/opt.h>
    #include <libswscale/swscale.h>
}

namespace rtsp {
    namespace server {
        std::mutex frame_mutex;
        cv::Mat global_frame;

        void build_rtp_header(RtpHeader *hdr, unsigned seq_num, unsigned int timestamp, unsigned int ssrc) {
            hdr->vpxcc = 0x80;
            hdr->mpayload = 96;
            hdr->sequence_number = htons(seq_num);
            hdr->timestamp = htonl(timestamp);
            hdr->ssrc = htonl(ssrc);
        }

        void capture_start_thread(const int device_id) {
            cv::VideoCapture cap("/home/jyj/Downloads/traffic.mp4"); // Replace "username" with your actual username


            if(!cap.isOpened()) {
                std::cerr << "Error: Unable to open the camera stream" << std::endl;
                return;
            }

            while (true) {
                cv::Mat frame;
                cap >> frame;

                if(frame.empty()) {
                    std::cerr << "Error: Frame is empty" << std::endl;
                    break;
                }
                {
                    std::lock_guard<std::mutex> lock(frame_mutex);
                    global_frame = frame.clone();
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }
            cap.release();
        }

        void rtp_streaming_thread(int sockfd, struct sockaddr_in cliaddr) {
            const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
            if (!codec) {
                std::cerr << "Codec H.264 not found" << std::endl;
                return;
            }

            AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
            if (!codec_ctx) {
                std::cerr << "Could not allocate video codec context" << std::endl;
                return;
            }

            codec_ctx->bit_rate = 400000;
            codec_ctx->width = global_frame.cols;
            codec_ctx->height = global_frame.rows;
            codec_ctx->time_base = {1, 30};
            codec_ctx->framerate = {30, 1};
            codec_ctx->gop_size = 10;
            codec_ctx->max_b_frames = 1;
            codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

            if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
                std::cerr << "Could not open codec" << std::endl;
                return;
            }

            AVFrame *frame = av_frame_alloc();
            frame->format = codec_ctx->pix_fmt;
            frame->width  = codec_ctx->width;
            frame->height = codec_ctx->height;
            av_image_alloc(frame->data, frame->linesize, frame->width, frame->height, codec_ctx->pix_fmt, 32);

            unsigned short sequence_number = 0;
            unsigned int timestamp = 0;
            unsigned int ssrc = 12345;
            socklen_t len = sizeof(cliaddr);
            const size_t max_packet_size = 1000 - RTP_HEADER_SIZE;

            SwsContext *sws_ctx = sws_getContext(global_frame.cols, global_frame.rows, AV_PIX_FMT_BGR24,
                                                 codec_ctx->width, codec_ctx->height, AV_PIX_FMT_YUV420P,
                                                 SWS_BICUBIC, nullptr, nullptr, nullptr);

            while (true) {
                cv::Mat bgr_frame;
                {
                    std::lock_guard<std::mutex> lock(frame_mutex);
                    if (global_frame.empty()) continue;
                    bgr_frame = global_frame.clone();
                }

                uint8_t *src_data[1] = { bgr_frame.data };
                int src_linesize[1] = { static_cast<int>(bgr_frame.step[0]) };
                sws_scale(sws_ctx, src_data, src_linesize, 0, codec_ctx->height, frame->data, frame->linesize);

                AVPacket pkt;
                av_new_packet(&pkt, 0);

                int ret = avcodec_send_frame(codec_ctx, frame);
                if (ret < 0) {
                    std::cerr << "Error sending frame to codec context" << std::endl;
                    break;
                }

                while (ret >= 0) {
                    ret = avcodec_receive_packet(codec_ctx, &pkt);
                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;
                    if (ret < 0) {
                        std::cerr << "Error during encoding" << std::endl;
                        return;
                    }

                    size_t offset = 0;
                    while (offset < pkt.size) {
                        size_t packet_size = std::min(max_packet_size, pkt.size - offset);
                        char rtp_packet[RTP_BUFFER_SIZE];
                        
                        rtsp::server::RtpHeader rtp_hdr;
                        build_rtp_header(&rtp_hdr, sequence_number++, timestamp, ssrc);
                        timestamp += 160;

                        if (offset + packet_size >= pkt.size) {
                            rtp_hdr.mpayload |= 0x80;
                        }

                        memcpy(rtp_packet, &rtp_hdr, RTP_HEADER_SIZE);
                        memcpy(rtp_packet + RTP_HEADER_SIZE, pkt.data + offset, packet_size);

                        if (sendto(sockfd, rtp_packet, packet_size + RTP_HEADER_SIZE, 0, (struct sockaddr*)&cliaddr, len) < 0) {
                            perror("Error sending RTP packet");
                            break;
                        }

                        offset += packet_size;
                    }
                    av_packet_unref(&pkt);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }

            avcodec_free_context(&codec_ctx);
            av_frame_free(&frame);
            sws_freeContext(sws_ctx);
        }
    }
}
