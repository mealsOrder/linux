#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      networkManager(new QNetworkAccessManager(this)),
      imageLabel(new QLabel(this)),
      fetchTimer(new QTimer(this)),
      saveButton(new QPushButton("Save Image", this)),
      urlInput(new QLineEdit(this)) {

    // URL 입력 필드 설정
    urlInput->setPlaceholderText("Enter image stream URL");

    // UI 레이아웃 설정
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(urlInput);
    topLayout->addWidget(saveButton);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(imageLabel);
    imageLabel->setAlignment(Qt::AlignCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(fetchTimer, &QTimer::timeout, this, &MainWindow::fetchImage);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::displayImage);

    // 주기적으로 이미지를 가져오도록 타이머 시작 (1초마다 요청)
    fetchTimer->start(1000);
}

MainWindow::~MainWindow() {}

void MainWindow::fetchImage() {
    // URL을 가져와 요청 전송
    QUrl url(urlInput->text());
    if (url.isValid()) {
        QNetworkRequest request(url);
        networkManager->get(request);
    } else {
        qDebug() << "Invalid URL";
    }
}

void MainWindow::displayImage(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        currentImage.loadFromData(imageData);

        if (!currentImage.isNull()) {
            imageLabel->setPixmap(QPixmap::fromImage(currentImage));
        } else {
            qDebug() << "Failed to load image from data";
        }
    } else {
        qDebug() << "Network error: " << reply->errorString();
    }
    reply->deleteLater();
}

void MainWindow::saveImage() {
    if (!currentImage.isNull()) {
        QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.jpg *.bmp)");
        if (!filePath.isEmpty()) {
            if (currentImage.save(filePath)) {
                qDebug() << "Image saved to:" << filePath;
            } else {
                qDebug() << "Failed to save image";
            }
        }
    } else {
        qDebug() << "No image to save";
    }
}
