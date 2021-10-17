#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QBuffer>
#include <QWidget>
#include<iostream>

using namespace cv;
using namespace std;




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


  private slots:
    void Video1();

private:
    Ui::MainWindow *ui;
    VideoCapture camera;
    QTimer fps_timer;


};
#endif // MAINWINDOW_H
