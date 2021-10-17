#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    time = new QTimer(this);
        time->start(10);

        connect(time, SIGNAL(timeout()), this, SLOT(readFrame()));

        counter = 0;

        cap.open(0);
        write.open("C:/Users/ELECTRON/Pictures/Saved Pictures/test.avi", VideoWriter::fourcc('M', 'P', '4', '2'), 30.0, Size(640, 480), true); // Save in the current directory, AVI video named test
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::mat2QImage(Mat cvImg)
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

void MainWindow::readFrame()
{
    cap >> frame;
       counter++;
       if(frame.empty())
       {
            qDebug()<<"frame is empty";
            cap.release();
       }

       if (counter <= 100)  // Only save 100 frames
       {
           qDebug() << "counter = " << counter;
           write.write(frame);  // Save video frame
       }
       ui->label->setPixmap(QPixmap::fromImage(mat2QImage(frame)));
}

