#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QSerialPort>


#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QUdpSocket>

#include <QtGamepad>

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
    void mcuwrite(QString);   //serial communicatio
    void mcuread();


    void udpread();            //udp communicaton
    void udpwrite(QString);

    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);





private:
    Ui::MainWindow *ui;


    QSerialPort *device;
    static const quint16 device_vendor_id = 9025;
    static const quint16 device_product_id = 67;
    QString device_port_name;
    bool device_is_available;
    QByteArray serialData;                 //serial communication
    QString serialBuffer;
    QString parsed_data;
    QString data1;
    QString data2;
    QString data3;
    QString data4;



   QUdpSocket *udpSocket;    //udp communication
   QString udpBuffer;
   QString udata1;
   QString udata2;
   QString udata3;
   QString udata4;


};
#endif // MAINWINDOW_H
