#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(&fps_timer,SIGNAL(timeout()),this,SLOT(VideoSend()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    camera.open(0);
    fps_timer.start(60);
}

void MainWindow::on_pushButton_2_clicked()
{

    fps_timer.stop();
    camera.release();
    this->close();
}

void MainWindow::VideoSend()
{

    Mat frame;
    camera.read(frame);


//        cv::HOGDescriptor hog;
//        hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

//        std::vector<cv::Rect> detections;
//            hog.detectMultiScale(frame, detections, 0, cv::Size(8, 8), cv::Size(32, 32), 1.2, 2);

//            for (auto& detection : detections) {
//                    ResizeBoxes(detection);
//                    cv::rectangle(frame, detection.tl(), detection.br(), cv::Scalar(255, 0, 0), 2);
//                }



    cvtColor(frame,frame,cv::COLOR_BGR2RGB);
    QImage image((unsigned char *)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->resize(image.width(),image.height());


}

//void MainWindow::ResizeBoxes(Rect &box)
//{
//    box.x += cvRound(box.width*0.1);
//        box.width = cvRound(box.width*0.8);
//        box.y += cvRound(box.height*0.06);
//        box.height = cvRound(box.height*0.8);
//}

