#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QUdpSocket>
#include <QTimer>
#include <QBuffer>

using namespace cv;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void VideoSend();
    void ResizeBoxes(cv::Rect& box);

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    VideoCapture camera;
    QTimer fps_timer;
};

#endif // WIDGET_H
