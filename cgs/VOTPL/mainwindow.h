#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QString>
#include <QWidget>

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QWebEngineView>


//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>

#include <QTimer>




//using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent * event);
    int counter=0;   //counter for speed


    void Buttons();
    void Gseane();
    void Plot();
    void Map();
    void Udp();
    void V_top();




public slots:
    void udpread();
    void udpWrite(QString);
    void realtimeDataSlot();



signals:

    void Top_Val(QString);
    void Side_Val(QString);
    void Back_Val(QString);


private:


    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QString udpBuffer;
       QString data1;
       QString data2;
       QString data3;
       QString data4;
       QString data5;
       QString data6;
       QString data7;
       QString data8;
       QString data9;
       QString data10;


    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsPixmapItem *top;
    QGraphicsPixmapItem *side;
    QGraphicsPixmapItem *back;


//    VideoCapture ptz;
    QTimer *timer1;
    QTimer *timer;




};
#endif // MAINWINDOW_H
