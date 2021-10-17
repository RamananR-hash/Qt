#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&fps_timer,SIGNAL(timeout()),this,SLOT(Video1()));
    camera.open(0);
    fps_timer.start(33);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Video1()
{
    cv::Mat frame;
    camera.read(frame);
    Mat t2 = imread("519164.jpg");

   //char *c2 = "new";

    //line(frame, Point(0, 0), Point(500, 500), Scalar(100, 105, 200), 3, 8);
   // rectangle(frame, Rect(100, 100, 150, 150), Scalar(150, 200, 170), 2, 8);
    putText(frame, "WHY", Point(150, 150), 1, 2, Scalar(200, 45, 160), 2, 8, false);//text

  //line

    Point p1 = Point(0,0);//Start point
    Point p2 = Point(500, 250);//End point
    Scalar color = Scalar(0, 0, 255);
    line(frame, p1, p2, color, 1, LINE_8);

    // rectangle
    Rect rect = Rect(100, 100, 300, 300);//Starting point; length and width
    Scalar color1 = Scalar(55, 55, 55);
    rectangle(frame, rect, color, 2, LINE_8);

    //ellipse
    Scalar color2 = Scalar(180, 90, 200);
    ellipse(frame, Point(frame.cols / 2, frame.rows / 2), Size(60, 180),45, 0, 360, color, 1, LINE_8);
    // Image center point of short axis, long axis, starting angle and range, line width


    //circle
    circle(frame, Point(50, 50), 50, Scalar(200, 50, 5), 2, LINE_8);
    //   center of circle radii color

    //polygon

    //ex.1
    Point pts[1][5];
    pts[0][0] = Point(100, 100);
    pts[0][1] = Point(80, 50);
    pts[0][2] = Point(20, 10);
    pts[0][3] = Point(20, 25);
    pts[0][4] = Point(100, 100);
    const Point* pp[] = { pts[0] };
    int np[] = {5 };//Points
    Scalar color3 = Scalar(220, 250, 220);
    fillPoly(frame, pp, np, 1, color, 8); ///1 means to draw an outline

  //ex.2

    Point pts2[1][5];
        pts[0][0] = Point(100, 100);
        pts[0][1] = Point(100, 200);
        pts[0][2] = Point(200, 200);
        pts[0][3] = Point(200, 100);
        pts[0][4] = Point(100, 100);

        Point pts3[1][5];
        pts2[0][0] = Point(210, 100);
        pts2[0][1] = Point(210, 200);
        pts2[0][2] = Point(310, 200);
        pts2[0][3] = Point(310, 100);
        pts2[0][4] = Point(210, 100);


        const Point* ppts[] = { pts[0], pts2[0] };
        int npt[] = { 5, 5 };
        Scalar color4 = Scalar(255, 0, 150);

        fillPoly(frame, ppts, npt, 2, color, 8);







    /*Randomlinedemo


    RNG rng(12345);//Generate random number seed
    Point p3;
    Point p4;
    //Mat r(800, 800, CV_8UC3, Scalar(255, 255, 255));

    for (int i = 0; i < 500; i++){
        p3.x = rng.uniform(0,frame.cols);
    p4.x = rng.uniform(0,frame.cols);
    p3.y = rng.uniform(0,frame.cols);
    p4.y = rng.uniform(0,frame.cols);
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    if (waitKey(50) > 0) {
    break;
    }
    line(frame, p3, p4, color, 2, 8);
    //namedWindow("HA", CV_WINDOW_NORMAL);
    //imshow("HA",frame);
    }*/





    cv::resize(frame, frame, cv::Size(), 1, 1);
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage image((unsigned char *)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->resize(image.width(),image.height());
}

