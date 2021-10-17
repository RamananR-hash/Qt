#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QLine>
#include <QChartView>
#include <QLineSeries>


QT_CHARTS_USE_NAMESPACE


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:






   void readSerial();
   //sensor_readingvoid updateTemperature(QString);

     void updateLCD(const QString);
    void updateRGB(QString);




    void on_lon_clicked();

    void on_loff_clicked();

    void on_pon_clicked();


    void on_poff_clicked();



    void on_dial_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
     double current;
     double vibration;
     double tempareture;
     double voltage;
     double intensity;

     QLineSeries *series;
      QChart *chart;
      QChartView *view;
};

#endif // DIALOG_H
