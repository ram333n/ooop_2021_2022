#include "mainwindow.h"
#include "inputwindow.h"
#include "donotdisturbwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAddTimer_triggered()
{
    InputWindow* inputWindow = new InputWindow(this);
    inputWindow->show();
}


void MainWindow::on_actionDoNotDisturb_triggered()
{
    DoNotDisturbWindow* doNotDisturbWindow=new DoNotDisturbWindow(this);
    doNotDisturbWindow->show();
}

