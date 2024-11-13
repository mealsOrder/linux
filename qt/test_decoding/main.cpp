#include <QApplication>
#include "imagestreamer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // RTP 스트림 URL (예: rtsp://localhost:8554/test)
    std::string streamUrl = "rtsp://localhost:8554/test"; // 실제 RTP URL로 변경

    // 스트리밍 간격 설정 (예: 30ms)
    ImageStreamer streamer(streamUrl, 30);
    streamer.resize(800, 600);
    streamer.show();

    return app.exec();
}
