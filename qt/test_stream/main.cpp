#include <QApplication>
#include "imagestreamer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 이미지 경로의 기본 경로 설정 (이미지가 저장된 디렉토리)
    QString basePath = "/home/jyj/workspace/qt/test_stream/images";  // 실제 경로로 변경

    // 스트리밍 간격 설정 (예: 1000ms = 1초)
    ImageStreamer streamer(basePath, 1000);
    streamer.resize(640, 480);
    streamer.show();

    return app.exec();
}
