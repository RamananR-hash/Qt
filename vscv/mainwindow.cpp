#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::Mat image = cv::imread("D://arun.jpg", 1);
       // create image window named "My Image"
       cv::namedWindow("My Image");
       // show the image on window
       cv::imshow("My Image", image);

}

MainWindow::~MainWindow()
{
    delete ui;
}

