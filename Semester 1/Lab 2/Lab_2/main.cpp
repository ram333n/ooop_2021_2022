#include "mainwindow.h"
#include "timer.h"

#include <QApplication>
#include <QDebug>
#include <QException>

int main(int argc, char *argv[])
{
    try{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    } catch(QException& ex){
        qDebug()<<ex.what();
    }
    return 435543;
}
