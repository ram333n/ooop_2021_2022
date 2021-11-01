#include "mainwindow.h"
#include "inputwindow.h"
#include "donotdisturbwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Smart timers");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAddTimer_triggered()
{
    inputWindow = new InputWindow(timers, currentIndex, ui->listTimersWidget);
    inputWindow->show();
}


void MainWindow::on_actionDoNotDisturb_triggered()
{
    doNotDisturbWindow = new DoNotDisturbWindow(doNotDisturbModeTimePoints, this);
    doNotDisturbWindow->show();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

