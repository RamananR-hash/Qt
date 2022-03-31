#include "mainwindow.h"
#include "ui_mainwindow.h"




#include<QHostAddress>
#include<QPixmap>
#include <QBuffer>
#include <QDebug>
#include <QKeyEvent>
#include<QImageReader>
#include <QString>
#include <QFile>

#include <QUrl>








MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

      Udp();
      Plot();

      web();


}

void MainWindow::Udp()
{
    udpSocket = new QUdpSocket(this);
    receiver.bind(QHostAddress::Any,6666);
    udpSocket->bind(QHostAddress::Any,5432); // udp recieving port
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpread()));   // udp slot
    connect(&receiver,SIGNAL(readyRead()),this,SLOT(video_receive_show()));
}


void MainWindow::video_receive_show()
{
    quint64 size = receiver.pendingDatagramSize();
    QByteArray buff;
    buff.resize(size);
    QHostAddress address ;
    quint16 port;
    receiver.readDatagram(buff.data(),buff.size(),&address,&port);
    buff = qUncompress(buff);
    QBuffer buffer(&buff);
    QImageReader reader(&buffer,"JPEG");
    QImage image = reader.read();
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->resize(image.width(),image.height());

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){

      on_UP_clicked();
           //qDebug()<<"left";
       }
       else if (event->key() == Qt::Key_S){
                   on_down_clicked();

       }

       else if (event->key() == Qt::Key_A){
        on_left_clicked();

       }
    else if (event->key() == Qt::Key_D){
            on_right_clicked();

    }
    else if (event->key() == Qt::Key_H){
        on_horen_clicked();

              //counter++;
               //MainWindow::udpWrite(QString("h%1").arg(counter));
    }
    else if (event->key() == Qt::Key_L){

        on_light_clicked();
              //counter--;
               //MainWindow::udpWrite(QString("h%1").arg(counter));
    }
    else if (event->key() == Qt::Key_K){
        on_light_clicked();


    }
    else if (event->key() == Qt::Key_Z){
       on_sos_clicked();


    }

    else if (event->key() == Qt::Key_X){

          on_sos_2_clicked();

    }

    else if (event->key() == Qt::Key_J){
        MainWindow::udpWrite(("j"));


    }
}
void MainWindow::Plot()
{


    //wave genaration
    ui->customPlot_1->addGraph();
    ui->customPlot_2->addGraph();
    ui->customPlot_3->addGraph();
    ui->customPlot_4->addGraph();
    ui->customPlot_5->addGraph();
    ui->customPlot_6->addGraph();

    //wave color
    ui->customPlot_1->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot_2->graph(0)->setPen(QPen(Qt::green));
    ui->customPlot_3->graph(0)->setPen(QPen(Qt::red));
    ui->customPlot_4->graph(0)->setPen(QPen(Qt::yellow));
    ui->customPlot_5->graph(0)->setPen(QPen(QColor(32, 203,217 ), 1, Qt::SolidLine));
    ui->customPlot_6->graph(0)->setPen(QPen(QColor(200, 64,213 ), 1, Qt::SolidLine));


    //if x axis is time we can use
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s");


    //set time for x axis
    ui->customPlot_1->xAxis->setTicker(timeTicker);
    ui->customPlot_5->xAxis->setTicker(timeTicker);
    ui->customPlot_6->xAxis->setTicker(timeTicker);

    //axis range set
    ui->customPlot_2->xAxis->setTicker(timeTicker);
    ui->customPlot_3->xAxis->setTicker(timeTicker);
    ui->customPlot_4->xAxis->setTicker(timeTicker);
    ui->customPlot_1->yAxis->setRange(0, 10);
    ui->customPlot_2->yAxis->setRange(0, 10);
    ui->customPlot_3->yAxis->setRange(0, 10);
    ui->customPlot_4->yAxis->setRange(0, 10);
    ui->customPlot_5->yAxis->setRange(0, 10);
    ui->customPlot_6->yAxis->setRange(0, 10);

    //axis name
    ui->customPlot_1->xAxis->setLabel("Time (Sec)");
    ui->customPlot_1->yAxis->setLabel("x");
    ui->customPlot_2->xAxis->setLabel("Time (Sec)");
    ui->customPlot_2->yAxis->setLabel("y");
    ui->customPlot_3->xAxis->setLabel("Time (Sec)");
    ui->customPlot_3->yAxis->setLabel("z");
    ui->customPlot_4->xAxis->setLabel("Time (Sec)");
    ui->customPlot_4->yAxis->setLabel("temp");
    ui->customPlot_5->xAxis->setLabel("Time (Sec)");
    ui->customPlot_5->yAxis->setLabel("voltag");
    ui->customPlot_6->xAxis->setLabel("Time (Sec)");
    ui->customPlot_6->yAxis->setLabel("curent");




    //axis name color
    ui->customPlot_1->xAxis->setLabelColor(Qt::white);
    ui->customPlot_1->yAxis->setLabelColor(Qt::white);
    ui->customPlot_2->xAxis->setLabelColor(Qt::white);
    ui->customPlot_2->yAxis->setLabelColor(Qt::white);
    ui->customPlot_3->xAxis->setLabelColor(Qt::white);
    ui->customPlot_3->yAxis->setLabelColor(Qt::white);
    ui->customPlot_4->xAxis->setLabelColor(Qt::white);
    ui->customPlot_4->yAxis->setLabelColor(Qt::white);
    ui->customPlot_5->xAxis->setLabelColor(Qt::white);
    ui->customPlot_5->yAxis->setLabelColor(Qt::white);
    ui->customPlot_6->xAxis->setLabelColor(Qt::white);
    ui->customPlot_6->yAxis->setLabelColor(Qt::white);

    //wave inner color
    ui->customPlot_1->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 50)));
    ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 20)));
    ui->customPlot_3->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->customPlot_4->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->customPlot_5->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    ui->customPlot_6->graph(0)->setBrush(QBrush(QColor(255, 0, 0, 20)));




    //axis color and thickness
    ui->customPlot_1->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_1->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_2->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_2->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_3->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_3->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_4->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_4->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_5->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_5->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_6->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot_6->yAxis->setBasePen(QPen(Qt::white, 1));



    //axis value line marking
    ui->customPlot_1->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_1->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_2->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_2->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_3->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_3->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_4->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_4->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_5->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_5->yAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_6->xAxis->setTickPen(QPen(Qt::white, 2));
    ui->customPlot_6->yAxis->setTickPen(QPen(Qt::white, 2));



    //axis sub value line coler
    ui->customPlot_1->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_1->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_2->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_2->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_3->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_3->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_4->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_4->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_5->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_5->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_6->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot_6->yAxis->setSubTickPen(QPen(Qt::white, 1));

    //axis value color
    ui->customPlot_1->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_1->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_3->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_3->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_4->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_4->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_5->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_5->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_6->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_6->yAxis->setTickLabelColor(Qt::white);



    //graph inner divider color and style
    ui->customPlot_1->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_1->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_2->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_2->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_3->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_3->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_4->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_4->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_5->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_5->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_6->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));
    ui->customPlot_6->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 0, Qt::DotLine));



    //if u want to remove starting 0 denote
    ui->customPlot_1->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_1->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_2->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_2->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_3->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_3->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_4->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_4->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_5->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_5->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_6->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot_6->yAxis->grid()->setZeroLinePen(Qt::NoPen);




    //graph backroung and style
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 500);
    axisRectGradient.setColorAt(0, QColor(0, 0, 0));
    ui->customPlot_1->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_2->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_3->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_4->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_5->axisRect()->setBackground(axisRectGradient);
    ui->customPlot_6->axisRect()->setBackground(axisRectGradient);



    //all backround color and style
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(0, 0, 0));
    ui->customPlot_1->setBackground(plotGradient);
    ui->customPlot_2->setBackground(plotGradient);
    ui->customPlot_3->setBackground(plotGradient);
    ui->customPlot_4->setBackground(plotGradient);
    ui->customPlot_5->setBackground(plotGradient);
    ui->customPlot_6->setBackground(plotGradient);



    //zoom control
    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot_6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);





    connect(&timer,SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    connect(&timer1,SIGNAL(timeout()), this, SLOT(Staticval()));
    // connect(&timer2,SIGNAL(timeout()), this, SLOT(Gviewtop()));
     //connect(&timer3,SIGNAL(timeout()), this, SLOT(Gviewside()));
     //connect(&timer4,SIGNAL(timeout()), this, SLOT(Gviewback()));
    timer.start(0);
    timer1.start(500);
    timer2.start(0);
    timer3.start(0);
    timer4.start(0);




}

void MainWindow::web()
{
    ui->widget->setUrl(commandLineUrlArgument());

}

QUrl MainWindow::commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
        for (const QString &arg : args.mid(1)) {
            if (!arg.startsWith(QLatin1Char('-')))
                return QUrl::fromUserInput(arg);
        }
return QUrl(QStringLiteral("https://www.google.com"));
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
        double val = data1.toDouble();
        double val1 = data2.toDouble();
        double val2 = data3.toDouble();
        double val3 = data4.toDouble();






      ui->customPlot_1->graph(0)->addData(key, val);
      ui->customPlot_2->graph(0)->addData(key, val1);
      ui->customPlot_3->graph(0)->addData(key, val2);
      ui->customPlot_4->graph(0)->addData(key, val3);
      ui->customPlot_5->graph(0)->addData(key, val1);
      ui->customPlot_6->graph(0)->addData(key, val2);




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

    ui->customPlot_5->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_5->replot();

    ui->customPlot_6->xAxis->setRange(key, 4, Qt::AlignRight);
    ui->customPlot_6->replot();


}

void MainWindow::Staticval()
{
    MainWindow::udpWrite(("o"));
}


void MainWindow::udpread()
{

    QHostAddress address ;
    quint16 port1;


    udpSocket->hasPendingDatagrams();
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());



   // while (udpSocket->hasPendingDatagrams()) {

           udpSocket->readDatagram(datagram.data(), datagram.size(),&address,&port1);
           udpBuffer += QString::fromStdString(datagram.toStdString());

           // qDebug() << udpBuffer;

            QStringList bufferSplit =udpBuffer.split("z");
                         if(bufferSplit.length() <20){


                               datagram.clear();
                     }
                     else
                     {
                            //qDebug() << bufferSplit;



                             data1=bufferSplit[0];   //a
                             data2=bufferSplit[1];   //gx
                             data3=bufferSplit[2];   //gr
                             data4=bufferSplit[3];   //gz
                             data5=bufferSplit[4];   //heading
                             data6=bufferSplit[5];   //s1 count
                             data7=bufferSplit[6];  //s1 lat
                             data8=bufferSplit[7];  //s1 lon
                             data9=bufferSplit[8];  //s1 speed
                             data10=bufferSplit[9];  //s2 count
                             data11=bufferSplit[10]; //s2 lat
                             data12=bufferSplit[11]; //s2 lon
                             data13=bufferSplit[12];  // s2 speed
                             data14=bufferSplit[13]; //in temp
                             data15=bufferSplit[14]; //out temp
                             data16=bufferSplit[15]; //current
                             data17=bufferSplit[16]; //voltage
                             data18=bufferSplit[17]; //s1 alt
                             data19=bufferSplit[18]; //y
                             //data20=bufferSplit[19];



                             udpBuffer="";
        // qDebug() << data4;

    //qDebug() << data1 << " " << data2 << " " << data3 << " " << data4 << " " << data5<< " " << data6<< " " << data7<< " " << data8<< " " << data9 << " " << data10<< " " << data11<< " " << data12<< " "<<data13<<"" << data14<< " " << data15<< " " << data16<< " " << data17<< " " << data18<< ""<< data19;

                 }
               //}

}




void MainWindow::udpWrite(QString command)
{
   QHostAddress ip = (QHostAddress)ui->lineEdit->text();
   quint16 port =8765;
   udpSocket->writeDatagram(command.toUtf8().data(),ip,port);
    //qDebug()<< command;

}






MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_UP_clicked()
{
 MainWindow::udpWrite(("a"));
}


void MainWindow::on_down_clicked()
{
       MainWindow::udpWrite(("b"));
}


void MainWindow::on_left_clicked()
{
     MainWindow::udpWrite(("c"));
}


void MainWindow::on_right_clicked()
{
 MainWindow::udpWrite(("d"));
}


void MainWindow::on_horen_clicked()
{
        MainWindow::udpWrite(("h"));
}


void MainWindow::on_light_clicked()
{
  MainWindow::udpWrite(("l"));
}


void MainWindow::on_sos_clicked()
{
  MainWindow::udpWrite(("s"));
}




void MainWindow::on_throtal_valueChanged(int value)
{
MainWindow::udpWrite(QString("t%1").arg(value));
}


void MainWindow::on_light_2_clicked()
{
     MainWindow::udpWrite(("k"));
}


void MainWindow::on_sos_2_clicked()
{
    MainWindow::udpWrite(("x"));
}


