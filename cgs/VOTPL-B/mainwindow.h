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


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <QTimer>




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

    void keyPressEvent(QKeyEvent * event);


    void Udp();
    void Plot();   


    void web();

    QUrl commandLineUrlArgument();






public slots:


    void udpread();
    void udpWrite(QString);
    void realtimeDataSlot();
    void Gviewtop();
    void Gviewside();
    void Gviewback();
    void Staticval();



signals:

    void Top_Val(QString);
    void Side_Val(QString);
    void Back_Val(QString);


private slots:
    void on_UP_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_horen_clicked();

    void on_light_clicked();

    void on_sos_clicked();


    void on_throtal_valueChanged(int value);

    void on_light_2_clicked();

    void on_sos_2_clicked();

    void on_progressBar_valueChanged(int value);

    void on_manual_clicked();

    void on_automatic_clicked();

    void on_semi_automatic_clicked();

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
       QString data11;
      QString data12;
       QString data13;
        QString data14;
         QString data15;
          QString data16;
            QString data17;
            QString data18;
            QString data19;
            QString data20;



       QTimer timer;
       QTimer timer1;
       QTimer timer2;
       QTimer timer3;
       QTimer timer4;


      QGraphicsScene *scene1;
       QGraphicsScene *scene2;
        QGraphicsScene *scene3;



};
#endif // MAINWINDOW_H
