#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QDebug>

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QtCore>
#include <QtGui>

#include <QDesktopWidget>
#include <QMainWindow>


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

   QImage mat2QImage(cv::Mat cvImg);

private slots:
    void on_start_clicked();

    void on_record_clicked();

    void on_close_clicked();
    void Video();
    void initCamera();
    void initVideo();

private:
    Ui::MainWindow *ui;
    VideoCapture camera;
    QTimer *time;
    VideoWriter write;
       Mat frame;
       int counter;
       int isRecorded;
       QGraphicsScene * scene;
        QGraphicsPixmapItem *top;
};
#endif // MAINWINDOW_H
