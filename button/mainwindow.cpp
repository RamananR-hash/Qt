#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix;


        pix.load(":/rsc/icons png/pin.png");
         QPixmap pix1 =pix.scaled(200,200);

           ui->pushButton->setIcon(pix1);
           ui->pushButton->setIconSize(pix1.rect().size());
           ui->pushButton->setFixedSize(200,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

