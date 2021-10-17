#include "mainwindow.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QApplication>





Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;
    serialBuffer = "";
     current=0.0;
     vibration=0.0;
     tempareture=36;
     intensity=120;
     voltage=24.8;
        ui->lcdNumber_4->display(tempareture);
          ui->lcdNumber_6->display(intensity);
          ui->lcdNumber->display(voltage);

    /*
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
    */

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}



/*void Dialog::on_red_slider_valueChanged(int value)
{

}*/

void Dialog::on_pushButton_clicked()
{
  //seconscreen arun;
 // arun.setModal(true);
  //arun. exec();


    QLineSeries *series = new QLineSeries();

        series->append(0,2);
        series->append(QPointF(2,6));
        series->append(3,8);
        series->append(7,9);
        series->append(11,3);

        *series << QPointF(11,2) << QPointF(15,5) << QPointF(18,4) << QPointF(19,2);

        QChart *chart = new QChart();
        //Hide legend
        chart->legend()->hide();
        //To associate series, this step is very important. You must associate series with qchart to render the data:
        chart->addSeries(series);
        //When OpenGL is enabled, qlineseries supports GPU drawing. Other chart types of QT are not supported.
        series->setUseOpenGL(true);
        //Create the default coordinate system (Cartesian coordinates)
        chart->createDefaultAxes();
        //Set chart title
        chart->setTitle(QStringLiteral("Qt line chart example"));

        QChartView *view = new QChartView(chart);
        //Turn on anti aliasing for better display
        view->setRenderHint(QPainter::Antialiasing);
        view->resize(400,300);
        //Show chart
        view->show();
}

void Dialog::on_lon_clicked()
{
   Dialog::updateRGB(QString("c%1"));
   intensity=150;
   ui->lcdNumber_6->display(intensity);
}

void Dialog::on_loff_clicked()
{
      Dialog::updateRGB(QString("d%1"));
      intensity=120;
       ui->lcdNumber_6->display(intensity);


}

void Dialog::on_pon_clicked()
{
      Dialog::updateRGB(QString("a%1"));
}

void Dialog::on_poff_clicked()
{
     Dialog::updateRGB(QString("b%1"));
}



void Dialog::readSerial()
{



      qDebug() <<  serialBuffer;
      /*QStringList bufferSplit =serialBuffer.split(",");
      if(bufferSplit.length() <3){
          serialData = arduino->readAll();
           serialBuffer  += QString::fromStdString(serialData.toStdString());

      }else{
          qDebug() << bufferSplit;
          qDebug() << "Couldn't write to serial!"; Dialog::updateLCD(bufferSplit[1]);
          serialBuffer="";
      }*/
}

void Dialog::updateLCD(const QString sensor_reading)
{
    ui->lcdNumber->display(sensor_reading);
}

void Dialog::updateRGB(QString command)
{


    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}









void Dialog::on_dial_valueChanged(int value)
{
    ui->lcdNumber_3->display(value);

    current = value*0.008;
    ui->lcdNumber_2->display(current);

    vibration= value*0.5;
    ui->lcdNumber_5->display(vibration);



    Dialog::updateRGB(QString("r%1").arg(value));
     qDebug() << value;
}


