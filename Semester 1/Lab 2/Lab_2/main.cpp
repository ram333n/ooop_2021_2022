#include "mainwindow.h"
#include "timer.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    Timer t(TimerType::Timer, QTime(0,0,34), "aboba");
    qDebug() << t.getInfoAboutTimer();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
