#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QString>
#include <QWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent * event);
    int counter=0;   //counter for speed

public slots:
    void udpread();
    void udpWrite(QString);

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QString udpBuffer;
    QString data1;
    QString data2;
    QString data3;
    QString data4;



};
#endif // MAINWINDOW_H
