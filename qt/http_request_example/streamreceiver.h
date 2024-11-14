#ifndef STREAMRECEIVER_H
#define STREAMRECEIVER_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QImage>

class StreamReceiver : public QThread {
    Q_OBJECT

public:
    explicit StreamReceiver(QObject *parent = nullptr);
    ~StreamReceiver();

signals:
    void frameCaptured(const QImage &image);  // 프레임이 캡처되면 신호를 발생

protected:
    void run() override;  // QThread의 run() 메서드 오버라이드

private:
    cv::VideoCapture cap;
};

#endif // STREAMRECEIVER_H
