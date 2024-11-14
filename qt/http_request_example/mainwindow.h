#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchImage();               // HTTP 요청을 통해 이미지를 가져오는 슬롯
    void displayImage(QNetworkReply *reply); // 이미지를 표시하는 슬롯
    void saveImage();                // 이미지를 저장하는 슬롯

private:
    QNetworkAccessManager *networkManager;
    QLabel *imageLabel;
    QTimer *fetchTimer;
    QPushButton *saveButton;
    QLineEdit *urlInput;
    QImage currentImage;
};

#endif // MAINWINDOW_H
