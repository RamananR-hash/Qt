#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    device_is_available = false;
    device_port_name = "";
    device = new QSerialPort;




    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == device_vendor_id){
                if(serialPortInfo.productIdentifier() == device_product_id){
                    device_port_name = serialPortInfo.portName();
                    device_is_available = true;
                }
            }
        }
    }

    if(device_is_available){
        // open and configure the serialport
        device->setPortName(device_port_name);
        device->open(QSerialPort::ReadWrite);
        device->setBaudRate(QSerialPort::Baud115200);
        device->setDataBits(QSerialPort::Data8);
        device->setParity(QSerialPort::NoParity);
        device->setStopBits(QSerialPort::OneStop);
        device->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(device, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        QMessageBox::warning(this, "Port error", "Couldn't find the device!");
    }
}

MainWindow::~MainWindow()
{
    if(device->isOpen()){
        device->close();
    }

    delete ui;
}


void MainWindow::readSerial()
{


    QString line = this->device->readLine();


    serialBuffer  += QString::fromStdString(line.toStdString());   // data recieve from agv mcu to agv mpu
    QStringList bufferSplit =serialBuffer.split("z");
   if(bufferSplit.length() <5)
          {
             line.clear();
                  }

              else
                 {
                    //qDebug() << bufferSplit;

                     data1=bufferSplit[0];
                     data2=bufferSplit[1];
                     data3=bufferSplit[2];
                     data4=bufferSplit[3];
                     serialBuffer="";

                  qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 ;



}
}

void MainWindow::update_data(QString command)
{
    if(device->isWritable()){
        device->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}




void MainWindow::on_pushButton_clicked()
{
    MainWindow::update_data(QString("a%1"));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
     MainWindow::update_data(QString("r%1").arg(value));

}
