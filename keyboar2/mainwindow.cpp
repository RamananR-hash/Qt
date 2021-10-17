#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QHostAddress>

#include <QBuffer>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){

           qDebug()<<"left";
       }
       else if (event->key() == Qt::Key_Right){

                   qDebug()<<"lright";
       }

       else if (event->key() == Qt::Key_Up){

   qDebug()<<"up";


       }
    else if (event->key() == Qt::Key_Down){

   qDebug()<<"down";


    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

