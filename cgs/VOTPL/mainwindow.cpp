#include "mainwindow.h"
#include "ui_mainwindow.h"




#include<QHostAddress>
#include<QPixmap>
#include<QImageReader>
#include <QBuffer>
#include <QDebug>
#include <QKeyEvent>
#include <QString>
#include <QFile>






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   timer = new QTimer(this);

    Buttons();
    Gseane();
    Plot();
    Map();
    Udp();
    V_top();





}


void MainWindow::Udp()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,5555); // udp recieving port
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpread()));   // udp slot
  // connect(this,SIGNAL(Top_Val(QString)),this,SLOT(V_top(QString)));
   //connect(this,SIGNAL(Side_Val(QString)),this,SLOT(V_side(QString)));

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
          MainWindow::udpWrite(("a"));
           //qDebug()<<"left";
       }
       else if (event->key() == Qt::Key_Right){
                   //qDebug()<<"lright";
                    MainWindow::udpWrite(("b"));
       }

       else if (event->key() == Qt::Key_Up){
           //qDebug()<<"up";
           MainWindow::udpWrite(("c"));
       }
    else if (event->key() == Qt::Key_Down){
               //qDebug()<<"down";
               MainWindow::udpWrite(("d"));
    }
    else if (event->key() == Qt::Key_H){
              counter++;
               MainWindow::udpWrite(QString("h%1").arg(counter));
    }
    else if (event->key() == Qt::Key_L){
              counter--;
               MainWindow::udpWrite(QString("h%1").arg(counter));
    }
}

void MainWindow::Buttons()
{
    QPixmap pix;
    pix.load(":/main_ icons/test123.png");
     QPixmap pix1 =pix.scaled(50,50);
       //ui->pushButton->setIcon(pix1);
       //ui->pushButton->setIconSize(pix1.rect().size());
    //ui->pushButton->setFixedSize(31,91);


}

void MainWindow::Gseane()
{
    scene1 = new QGraphicsScene();
     scene1->setSceneRect(50,50,50,50);
      scene1->setBackgroundBrush(Qt::black);



//     scene2 = new QGraphicsScene();
//      scene2->setSceneRect(50,50,50,50);
//       scene2->setBackgroundBrush(Qt::black);

//      scene3 = new QGraphicsScene();
//       scene3->setSceneRect(50,50,50,50);
//        scene3->setBackgroundBrush(Qt::black);
}

void MainWindow::Plot()
{
    //wave genaration
    ui->customPlot_1->addGraph();
    ui->customPlot_2->addGraph();
    ui->customPlot_3->addGraph();
    ui->customPlot_4->addGraph();

    //wave color
    ui->customPlot_1->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_2->graph(0)->setPen(QPen(Qt::green));
    ui->customPlot_3->graph(0)->setPen(QPen(Qt::red));
    ui->customPlot_4->graph(0)->setPen(QPen(Qt::yellow));


    //if x axis is time we can use
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s");


    //set time for x axis
    ui->customPlot_1->xAxis->setTicker(timeTicker);
    ui->customPlot_2->xAxis->setTicker(timeTicker);
    ui->customPlot_3->xAxis->setTicker(timeTicker);
    ui->customPlot_4->xAxis->setTicker(timeTicker);

    //axis range set
    ui->customPlot_1->yAxis->setRange(0, 10);
    ui->customPlot_2->yAxis->setRange(0, 10);
    ui->customPlot_3->yAxis->setRange(0, 10);
    ui->customPlot_4->yAxis->setRange(0, 10);

    //axis name
    ui->customPlot_1->xAxis->setLabel("Time (Sec)");
    ui->customPlot_1->yAxis->setLabel("Temperature (C)");
    ui->customPlot_2->xAxis->setLabel("Time (Sec)");
    ui->customPlot_2->yAxis->setLabel("Pressure (Pa) ");
    ui->customPlot_3->xAxis->setLabel("Time (Sec)");
    ui->customPlot_3->yAxis->setLabel("Soil strength (kPa)");
    ui->customPlot_4->xAxis->setLabel("Time (Sec)");
    ui->customPlot_4->yAxis->setLabel("Depth (m)");


    //axis name color
    ui->customPlot_1->xAxis->setLabelColor(Qt::white);
    ui->customPlot_1->yAxis->setLabelColor(Qt::white);
    ui->customPlot_2->xAxis->setLabelColor(Qt::white);
    ui->customPlot_2->yAxis->setLabelColor(Qt::white);
    ui->customPlot_3->xAxis->setLabelColor(Qt::white);
    ui->customPlot_3->yAxis->setLabelColor(Qt::white);
    ui->customPlot_4->xAxis->setLabelColor(Qt::white);
    ui->customPlot_4->yAxis->setLabelColor(Qt::white);

    //wave inner color
    ui->customPlot_1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 50)));
    ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 20)));
    ui->customPlot_3->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->customPlot_4->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));


    //axis color and thickness
    ui->customPlot_1->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_1->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_2->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_2->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_3->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_3->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_4->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_4->yAxis->setBasePen(QPen(Qt::white, 1));

    //axis value line marking
    ui->customPlot_1->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_1->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_2->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_2->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_3->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_3->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_4->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_4->yAxis->setTickPen(QPen(Qt::white, 2));

    //axis sub value line coler
    ui->customPlot_1->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_1->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_2->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_2->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_3->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_3->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_4->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_4->yAxis->setSubTickPen(QPen(Qt::white, 1));

    //axis value color
    ui->customPlot_1->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_1->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_3->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_3->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_4->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_4->yAxis->setTickLabelColor(Qt::white);



    //graph inner divider color and style
    ui->customPlot_1->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_1->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_3->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_3->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_4->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_4->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));



    //if u want to remove starting 0 denote
    ui->customPlot_1->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_1->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_2->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_3->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_3->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_4->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_4->yAxis->grid()->setZeroLinePen(Qt::NoPen);


    //graph backroung and style
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 500);
    axisRectGradient.setColorAt(0, QColor(0, 0, 0));
    ui->customPlot_1->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_2->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_3->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_4->axisRect()->setBackground(axisRectGradient);



    //all backround color and style
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(0, 0, 0));
    ui->customPlot_1->setBackground(plotGradient);
    ui->customPlot_2->setBackground(plotGradient);
    ui->customPlot_3->setBackground(plotGradient);
    ui->customPlot_4->setBackground(plotGradient);

    //zoom control
    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);



  connect(timer,SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  timer->start(0); // Interval 0 means to refresh as fast as possible




}

void MainWindow::Map()
{


    ui->MapView->setUrl(QUrl("qrc:/webgl-tilt-rotation/sample.html"));


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
        double val = data5.toDouble();
        double val1 = data6.toDouble();
        double val2 = data7.toDouble();
        double val3 = data8.toDouble();






      ui->customPlot_1->graph(0)->addData(key, val);
      ui->customPlot_2->graph(0)->addData(key, val1);
      ui->customPlot_3->graph(0)->addData(key, val2);
      ui->customPlot_4->graph(0)->addData(key, val3);


     // qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << "" << data5;

      lastPointKey = key;
    }

    ui->customPlot_1->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_1->replot();

    ui->customPlot_2->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_2->replot();

    ui->customPlot_3->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_3->replot();

    ui->customPlot_4->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_4->replot();




}


void MainWindow::udpread()
{
    QHostAddress address ;
    quint16 port1;

    while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
           udpSocket->readDatagram(datagram.data(), datagram.size(),&address,&port1);
           udpBuffer += QString::fromStdString(datagram.toStdString());

            //qDebug() <<udpBuffer;

            QStringList bufferSplit =udpBuffer.split("z");
                         if(bufferSplit.length() <10){


                               datagram.clear();
                     }
                     else
                     {
                            //qDebug() << bufferSplit;



                             data1=bufferSplit[0];
                             data2=bufferSplit[1];
                             data3=bufferSplit[2];
                             data4=bufferSplit[3];
                             data5=bufferSplit[4];
                             data6=bufferSplit[5];
                             data7=bufferSplit[6];
                             data8=bufferSplit[7];
                             data9=bufferSplit[8];
                             udpBuffer="";


//                             emit Top_Val(data2);
//                             emit Side_Val(data3);
//                             emit Back_Val(data4);


                             //qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << " " << data5<< " " << data6<< " " << data7<< " " << data8<< " " << data9;

                 }
               }

}




void MainWindow::udpWrite(QString command)
{
   // QHostAddress ip = (QHostAddress)ui->label_2->text();
   // quint16 port1 = 8888;
    //udpSocket->writeDatagram(command.toUtf8().data(),ip,port1);
     //qDebug()<< command;

}

void MainWindow::V_top()
{

    int value1=data2.toInt();
  // qDebug()<<val<<val1<<val2;


    scene1->clear();

    QGraphicsPixmapItem *pm1 = scene1->addPixmap( QPixmap(":/images/image/top_view_agv.png").scaled(150, 150));
    //pm1->setPos(40,0);
    QPointF offset = pm1->sceneBoundingRect().center();
    QTransform transform;
    transform.translate(offset.x() ,offset.y());
    transform.rotate(value1);
    transform.translate(-offset.x(),-offset.y());
    pm1->setTransform(transform);



   //QGraphicsPixmapItem *pm2 = scene1->addPixmap( QPixmap(":/images/image/side_view_agv.png").scaled(150, 150));
    //pm2->setPos(80,0);

//    QPointF offset1 = pm2->sceneBoundingRect().center();
//    QTransform transform1;
//    transform1.translate(offset1.x(),offset1.y());
//    transform1.rotate(10);
//    transform1.translate(-offset1.x(),-offset1.y());
//    pm2->setTransform(transform1);


//    QGraphicsPixmapItem *pm3 = scene1->addPixmap( QPixmap(":/images/image/back_view_agv.png").scaled(150, 150));
//    QPointF offset2 = pm3->sceneBoundingRect().center();
//    QTransform transform2;
//    transform2.translate(offset2.x(),offset2.y());
//    transform2.rotate(10);
//    transform.translate(-offset2.x(),-offset2.y());
//    pm3->setTransform(transform2);

   QGraphicsPixmapItem *combos1 = scene1->addPixmap( QPixmap(":/images/image/bomoss.png").scaled(250, 250) );
   combos1->setPos(-67,-42);

//    QGraphicsPixmapItem *combos2 = scene2->addPixmap( QPixmap(":/images/image/comboss1.png").scaled(225, 225) );
//    combos2->setPos(-40,-36);

//    QGraphicsPixmapItem *combos3 = scene3->addPixmap( QPixmap(":/images/image/comboss1.png").scaled(225, 225) );
//    combos3->setPos(-40,-36);


   ui->graphicsView_top->setScene(scene1);
}




MainWindow::~MainWindow()
{
    delete ui;
}





