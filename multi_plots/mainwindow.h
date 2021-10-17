#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  void plote();

private slots:

    void realtimeDataSlot();
    void update_data(QString);
    void readSerial();



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
     QString data5;

    QTimer timer;



};
#endif // MAINWINDOW_H
