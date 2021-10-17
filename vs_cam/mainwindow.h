#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QBuffer>
#include <vector>

using namespace std;
using namespace cv;
using namespace cv::ml;


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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void VideoSend();
    //void ResizeBoxes(cv::Rect& box);


private:
    Ui::MainWindow *ui;

    VideoCapture camera;
    QTimer fps_timer;

};
#endif // MAINWINDOW_H
