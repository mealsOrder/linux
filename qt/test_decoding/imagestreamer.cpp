#include "imagestreamer.h"
#include <QDebug>

ImageStreamer::ImageStreamer(const std::string& streamUrl, int interval, QWidget* parent)
    : QLabel(parent), streamUrl(streamUrl) {

    // FFmpeg를 사용하여 RTP 스트림 초기화
    cap.open(streamUrl, cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        qDebug() << "RTP 스트림을 열 수 없습니다: " << QString::fromStdString(streamUrl);
        return;
    }

    // QTimer 설정 - interval 간격으로 이미지를 업데이트
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ImageStreamer::updateImage);
    timer->start(interval);
}

ImageStreamer::~ImageStreamer() {
    // VideoCapture 해제
    if (cap.isOpened()) {
        cap.release();
    }
}

void ImageStreamer::updateImage() {
    cv::Mat frame;
    if (!cap.read(frame)) {  // 스트림에서 프레임을 읽음
        qDebug() << "프레임을 읽을 수 없습니다. 스트림을 종료합니다.";
        timer->stop();
        close();
        return;
    }

    // H.264 디코딩된 프레임을 RGB로 변환
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage qImg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

    // QLabel에 QPixmap으로 표시
    this->setPixmap(QPixmap::fromImage(qImg).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
