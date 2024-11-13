#ifndef STREAM_H
#define STREAM_H

#include <QLabel>
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <string>

class Stream : public QLabel {
    Q_OBJECT

public:
    Stream(const std::string& streamUrl, int interval, QWidget* parent = nullptr);
    ~Stream();

private slots:
    void updateImage();

private:
    std::string streamUrl; // RTP stream URL
    cv::VideoCapture cap;  // FFmpeg & OpenCV , RTP stream receive
    QTimer* timer;
};

#endif // STREAM_H
