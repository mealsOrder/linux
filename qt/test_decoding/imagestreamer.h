#ifndef IMAGESTREAMER_H
#define IMAGESTREAMER_H

#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <string>

class ImageStreamer : public QLabel {
    Q_OBJECT

public:
    ImageStreamer(const std::string& streamUrl, int interval, QWidget* parent = nullptr);
    ~ImageStreamer();

private slots:
    void updateImage();

private:
    std::string streamUrl; // RTP stream URL
    cv::VideoCapture cap;  // FFmpeg & OpenCV , RTP stream receive
    QTimer* timer;
};

#endif // IMAGESTREAMER_H
