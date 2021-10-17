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

    //wave genaration
    ui->customPlot_1->addGraph();
    ui->customPlot_2->addGraph();
    ui->customPlot_3->addGraph();

    //wave color
    ui->customPlot_1->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot_2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
    ui->customPlot_3->graph(0)->setPen(QPen(Qt::green));


    //if x axis is time we can use
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    //set time for x axis
    ui->customPlot_1->xAxis->setTicker(timeTicker);
    ui->customPlot_2->xAxis->setTicker(timeTicker);
    ui->customPlot_3->xAxis->setTicker(timeTicker);

    //axis range set
    ui->customPlot_1->yAxis->setRange(0, 1000);
    ui->customPlot_2->yAxis->setRange(0, 1000);
    ui->customPlot_3->yAxis->setRange(0, 1000);

    //double side box
//    ui->customPlot_1->axisRect()->setupFullAxesBox();
//    ui->customPlot_2->axisRect()->setupFullAxesBox();
//    ui->customPlot_3->axisRect()->setupFullAxesBox();

    //wave inner color
    ui->customPlot_1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot_3->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    //axis color and thickness
    ui->customPlot_1->xAxis->setBasePen(QPen(Qt::red, 3));
    ui->customPlot_1->yAxis->setBasePen(QPen(Qt::red, 3));


    //axis value line marking
    ui->customPlot_1->xAxis->setTickPen(QPen(Qt::green, 2));
    ui->customPlot_1->yAxis->setTickPen(QPen(Qt::green, 2));


    //axis sub value line coler
    ui->customPlot_1->xAxis->setSubTickPen(QPen(Qt::green, 1));
    ui->customPlot_1->yAxis->setSubTickPen(QPen(Qt::green, 1));


    //axis value color
    ui->customPlot_1->xAxis->setTickLabelColor(Qt::green);
    ui->customPlot_1->yAxis->setTickLabelColor(Qt::green);


    //graph inner divider color and style
    ui->customPlot_1->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot_1->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));

    //graph multi inner divider color ,style and visiblity
    ui->customPlot_1->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot_1->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot_1->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot_1->yAxis->grid()->setSubGridVisible(true);


    //if u want to remove starting 0 denote
    ui->customPlot_2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_2->yAxis->grid()->setZeroLinePen(Qt::NoPen);

    //graph backroung and style
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->customPlot_1->axisRect()->setBackground(axisRectGradient);

    //all backround color and style
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->customPlot_1->setBackground(plotGradient);


    //both the axis end style
    ui->customPlot_1->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot_1->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);



    //zoom control
    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot_1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot_1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_1->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->customPlot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_2->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->customPlot_3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot_3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_3->yAxis2, SLOT(setRange(QCPRange)));

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




      ui->customPlot_1->graph(0)->addData(key, val);
      ui->customPlot_2->graph(0)->addData(key, val1);
      ui->customPlot_3->graph(0)->addData(key, val2);

      qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << "" << data5;

      lastPointKey = key;
    }

    ui->customPlot_1->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->customPlot_1->replot();

    ui->customPlot_2->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->customPlot_2->replot();

    ui->customPlot_3->xAxis->setRange(key, 20, Qt::AlignRight);
    ui->customPlot_3->replot();




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





