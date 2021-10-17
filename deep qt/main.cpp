#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(1300, 650);
    w.setWindowTitle("DEEP");
    w.show();

    return a.exec();
}
