#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    time = new QTimer(this);
    isRecorded = false;


     connect(time,SIGNAL(timeout()),this,SLOT(Video()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::mat2QImage(cv::Mat cvImg)
{
    QImage qImg;

        if (cvImg.channels() == 3)                             //3 channels color image
        {
            cv::cvtColor(cvImg, cvImg, cv::COLOR_BGR2RGB);
            qImg = QImage((const unsigned char*)(cvImg.data),
                          cvImg.cols, cvImg.rows,
                          cvImg.cols*cvImg.channels(),
                          QImage::Format_RGB888);
        }

        else if (cvImg.channels() == 1)                    //grayscale image
        {
            qImg = QImage((const unsigned char*)(cvImg.data),
                          cvImg.cols, cvImg.rows,
                          cvImg.cols*cvImg.channels(),
                          QImage::Format_Indexed8);
        }

        else
        {
            qImg = QImage((const unsigned char*)(cvImg.data),
                          cvImg.cols, cvImg.rows,
                          cvImg.cols*cvImg.channels(),
                          QImage::Format_RGB888);
        }
        return qImg;
}

void MainWindow::initCamera()
{
    camera.open(0);
       if(camera.isOpened())
       {
           qDebug() << "Camera successfully connected.";
       }
}

void MainWindow::initVideo()
{
    std::string filename =  "C:/Users/ELECTRON/Pictures/Saved Pictures/test1.avi";
       int fcc =   VideoWriter::fourcc('D','I','V','X');
       int fps =   30;
       cv::Size frameSize(camera.get(CAP_PROP_FRAME_WIDTH),camera.get(CAP_PROP_FRAME_HEIGHT));
        write = cv::VideoWriter(filename,fcc,fps,frameSize);
        //write.open("C:/Users/ELECTRON/Pictures/Saved Pictures/test1.avi", VideoWriter::fourcc('M', 'P', '4', '2'), 30.0, Size(640, 480), true);
}


void MainWindow::Video()
{

    if(camera.read(frame)){

            if(isRecorded)
            {
                write.write(frame);
                 cv::putText(frame,"[REC]",cv::Point(0,30),5,1,cv::Scalar(0,0,225));

            }
//            scene = new QGraphicsScene();
//             scene->setSceneRect(-100,-100,100,100);


//                QGraphicsPixmapItem *top = scene->addPixmap(QPixmap::fromImage(mat2QImage(frame)) );
//                top->setPos(-300,-300);
//                 ui->graphicsView->setScene(scene);
           ui->video->setPixmap(QPixmap::fromImage(mat2QImage(frame)));
        }




}



void MainWindow::on_start_clicked()
{
    time->start(33);
    initCamera();

}


void MainWindow::on_record_clicked()
{


    isRecorded = !isRecorded;
    if(isRecorded)
            initVideo();


}

void MainWindow::on_close_clicked()
{
    if(camera.isOpened())
       {
           // Disconnect camera
           camera.release();
           qDebug() << "Camera successfully disconnected.";
       }
       time->stop();
}




