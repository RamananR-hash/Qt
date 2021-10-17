#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,8888);
    connect(&fps_timer,SIGNAL(timeout()),this,SLOT(VideoSend()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_open_clicked()
{
    camera.open(0);
    fps_timer.start(33);
}

void Widget::on_pushButton_close_clicked()
{
    fps_timer.stop();
    camera.release();
    this->close();
}
void Widget::VideoSend()
{
    QHostAddress dstip = (QHostAddress)(ui->lineEdit_ip->text());
    quint16 dstport = ui->lineEdit_port->text().toInt();
    Mat frame;
    camera.read(frame);


    cv::HOGDescriptor hog;
          hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

          std::vector<cv::Rect> detections;
              hog.detectMultiScale(frame, detections, 0, cv::Size(8, 8), cv::Size(32, 32), 1.2, 2);

              for (auto& detection : detections) {
                      ResizeBoxes(detection);
                      cv::rectangle(frame, detection.tl(), detection.br(), cv::Scalar(255, 0, 0), 2);
                  }



    cvtColor(frame,frame,cv::COLOR_BGR2RGB);
    QImage image((unsigned char *)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label_video->setPixmap(QPixmap::fromImage(image));
    ui->label_video->resize(image.width(),image.height());
    QByteArray byte;
    QBuffer buff(&byte);
    buff.open(QIODevice::WriteOnly);
    image.save(&buff,"JPEG");
    QByteArray ss = qCompress(byte,5);
    udpSocket->writeDatagram(ss,dstip,dstport);
}

void Widget::ResizeBoxes(Rect &box)
{
           box.x += cvRound(box.width*0.1);
           box.width = cvRound(box.width*0.8);
           box.y += cvRound(box.height*0.06);
           box.height = cvRound(box.height*0.8);
}
