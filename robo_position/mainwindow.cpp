#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   scene = new QGraphicsScene();
   scene->setSceneRect(0,0,300,300);

    // a blue background
   // scene->setBackgroundBrush(Qt::blue);



    // a gradient background
    // QRadialGradient gradient(0, 0, 10);
    // gradient.setSpread(QGradient::PadSpread);
     //scene->setBackgroundBrush(gradient);

    //scene->setForegroundBrush(QColor(255, 255, 255, 127));

    // a grid foreground
    // scene->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));

 // QPixmap  bgPixmap(":/image/enemy.png");

  // QPixmap scaled = bgPixmap.scaled(QSize(600, 500));



       // QGraphicsPixmapItem *pm = scene->addPixmap( QPixmap(":/image/enemy.png").scaled(200, 200) );


         // pm->setPos(200,200);



         // pm->setTransform(QTransform().translate(150,150).rotate(position).translate(-150, -150));

           // Rotate an item 45 degrees around (x, y).
          //pm->setTransform(QTransform().translate(100,100).rotate(val).translate(-100, -100));

         //pm->setOffset( -0.5 * QPointF( width(), height() ) );


       // ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    QGraphicsPixmapItem *pm = scene->addPixmap( QPixmap(":/image/enemy.png").scaled(200, 200) );
      pm->setPos(0,0);
//         pm->setTransform(QTransform().translate(150,150).rotate(val).translate(-150, -150));
//         ui->graphicsView->setScene(scene);

     QPointF offset = pm->sceneBoundingRect().center();
     QTransform transform;
     transform.translate(offset.x(),offset.y());
     transform.rotate(position);
     transform.translate(-offset.x(),-offset.y());
     pm->setTransform(transform);

     ui->graphicsView->setScene(scene);

    scene->update();







      }

