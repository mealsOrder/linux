#ifndef IMAGESTREAMER_H
#define IMAGESTREAMER_H

#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>

class ImageStreamer : public QLabel {
    Q_OBJECT

public:
    ImageStreamer(const QString& basePath, int interval, QWidget* parent = nullptr);

private slots:
    void updateImage();

private:
    QString basePath;      // 이미지 경로의 기본 경로 (예: "path/to/images/")
    int currentIndex;      // 현재 이미지 번호
    QTimer* timer;         // QTimer 객체
};

#endif // IMAGESTREAMER_H
