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
    plote();



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

void MainWindow::plote()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(2)->setPen(QPen(Qt::green));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(0, 1000);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&timer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    timer.start(0); // Interval 0 means to refresh as fast as possible
 }



void MainWindow::realtimeDataSlot()
{


    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    //qDebug() <<key;
    static double lastPointKey = 0;



    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        double val = data2.toDouble();
        double val1 = data3.toDouble();
        double val2 = data4.toDouble();




      ui->customPlot->graph(0)->addData(key, val);
      ui->customPlot->graph(1)->addData(key, val1);
      ui->customPlot->graph(2)->addData(key, val2);
      qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << "" << data5;

      lastPointKey = key;
    }

    ui->customPlot->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->customPlot->replot();



}

void MainWindow::readSerial()
{


    QString line = this->device->readLine();


    serialBuffer  += QString::fromStdString(line.toStdString());   // data recieve from agv mcu to agv mpu
    QStringList bufferSplit =serialBuffer.split("z");
   if(bufferSplit.length() <6)
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
                     data5=bufferSplit[4];
                     serialBuffer="";

                 // qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 ;



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





