#include "imagestreamer.h"
#include <QFileInfo>
#include <QDebug>
ImageStreamer::ImageStreamer(const QString& basePath, int interval, QWidget* parent)
    : QLabel(parent), basePath(basePath), currentIndex(1) {  // 이미지 번호를 1로 시작

    // QTimer 설정 - interval 간격으로 이미지를 업데이트
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ImageStreamer::updateImage);
    timer->start(interval);
}

void ImageStreamer::updateImage() {
    // 현재 인덱스의 이미지 파일 경로 생성 (예: "path/to/images/1.png", "path/to/images/2.png" ...)
    QString imagePath = QString("%1/output_%2.png").arg(basePath).arg(currentIndex, 4, 10, QChar('0'));

        // 이미지 파일이 존재하는지 확인
        QFileInfo checkFile(imagePath);
        if (!checkFile.exists() || !checkFile.isFile()) {
            // 이미지 파일이 존재하지 않으면 프로그램 종료

            timer->stop();   // 타이머 정지
            close();         // QLabel 창 닫기
            qDebug() << "Do not load images" << '\n';
            return;
        }

    cv::Mat img = cv::imread(imagePath.toStdString(), cv::IMREAD_COLOR);

    if (img.empty()) {  // 이미지가 더 이상 없을 경우 종료d
        timer->stop();   // 타이머 정지
        close();         // QLabel 창 닫기
        return;
    }

    // OpenCV Mat을 QImage로 변환하여 QLabel에 표시
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    QImage qImg(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    this->setPixmap(QPixmap::fromImage(qImg).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 다음 이미지 번호로 이동
    currentIndex++;
}
