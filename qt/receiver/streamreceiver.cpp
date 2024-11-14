#include "streamreceiver.h"
#include <QDebug>

StreamReceiver::StreamReceiver(QObject *parent)
    : QThread(parent) {
    std::string pipeline = "udpsrc port=5004 ! application/x-rtp, payload=96 ! "
                           "rtph264depay ! avdec_h264 ! videoconvert ! appsink";
    cap.open(pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        qWarning() << "Error: Could not open RTP stream for reading";
    }
}

StreamReceiver::~StreamReceiver() {
    cap.release();
}

void StreamReceiver::run() {
    cv::Mat frame;
    while (cap.isOpened()) {
        cap >> frame;
        if (frame.empty()) {
            qWarning() << "Error: Empty frame received from RTP stream";
            break;
        }

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage qImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

        emit frameCaptured(qImage);  // 프레임이 캡처되면 메인 스레드로 신호 전송
        QThread::msleep(33);         // 약 30FPS로 프레임 전송
    }
}
