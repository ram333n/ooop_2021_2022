#include "mainwindow.h"

#include <QApplication>
#include "doctest.h"

int main(int argc, char *argv[])
{
    doctest::Context runner;
    runner.run();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

