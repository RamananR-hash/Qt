#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QHostAddress>

#include <QBuffer>
#include <QDebug>
#include <QKeyEvent>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any,5555); // udp recieving port

    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpread()));   // udp slot

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
                         if(bufferSplit.length() <5){


                               datagram.clear();
                     }
                     else
                     {
                            //qDebug() << bufferSplit;

                             udpBuffer="";
                             data1=bufferSplit[0];
                             data2=bufferSplit[1];
                             data3=bufferSplit[2];
                             data4=bufferSplit[3];

                             qInfo() << data1 << " " << data2 << " " << data3 << " "<<data4;

                 }
               }

}

void MainWindow::udpWrite(QString command)
{
    QHostAddress ip = (QHostAddress)ui->label_2->text();
    quint16 port1 = 8888;
    udpSocket->writeDatagram(command.toUtf8().data(),ip,port1);
     //qDebug()<< command;

}
MainWindow::~MainWindow()
{
    delete ui;
}

