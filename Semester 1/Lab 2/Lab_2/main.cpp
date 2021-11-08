#include "mainwindow.h"
#include "timer.h"

#include <QApplication>
#include <QDebug>
#include <QException>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
