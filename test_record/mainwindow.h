#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include "opencv2/opencv.hpp"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   QImage mat2QImage(cv::Mat cvImg);

  private slots:
      void readFrame();

private:
    Ui::MainWindow *ui;
    QTimer *time;

       Mat frame;

       VideoCapture cap;
       VideoWriter write;

       int counter;  // Number of recording frames
};
#endif // MAINWINDOW_H
