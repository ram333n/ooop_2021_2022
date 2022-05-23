#include "mainwindow.h"
#include "doctest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    doctest::Context runner;
    runner.run();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
