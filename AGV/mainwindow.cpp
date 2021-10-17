#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QSerialPort>
#include <QSerialPortInfo>


#include <QHostAddress>

#include <QDebug>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,8888); // udp recieving port

    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpread()));   // udp slot



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
        QObject::connect(device, SIGNAL(readyRead()), this, SLOT(mcuread()));
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




void MainWindow::mcuread()
{

         QString line = this->device->readLine();

          MainWindow::udpwrite(QString(line));

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

                       //qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 ;


        }
}

void MainWindow::udpread()
{

    QHostAddress address ;
    quint16 port;


    while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
           udpSocket->readDatagram(datagram.data(), datagram.size(),&address,&port);
           udpBuffer += QString::fromStdString(datagram.toStdString());

            //qDebug() <<serialBuffer;

            QStringList bufferSplit1 =udpBuffer.split(",");
                         if(bufferSplit1.length() <5){


                               datagram.clear();
                     }
                     else
                     {
                            //qDebug() << bufferSplit;


                             udata1=bufferSplit1[0];
                             udata2=bufferSplit1[1];
                             udata3=bufferSplit1[2];
                             udata4=bufferSplit1[3];

                             udpBuffer="";
                             //qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << endl;


                 }
               }

}





void MainWindow::udpwrite(QString commend)
{

     QHostAddress ip = (QHostAddress)ui->lineEdit->text();
     quint16 port1 =6666;                                                // agv mpu send data to server mpu
     udpSocket->writeDatagram(commend.toUtf8().data(),ip,port1);
     //qDebug() <<commend;
}




void MainWindow::mcuwrite(QString command)
{
    if(device->isWritable()){
        device->write(command.toStdString().c_str());       // agv mpu send data to agv mcu
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}






void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    MainWindow::mcuwrite(QString("r%1").arg(value));
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    MainWindow::mcuwrite(QString("g%1").arg(value));
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    MainWindow::mcuwrite(QString("b%1").arg(value));
    qDebug() << value;
}






