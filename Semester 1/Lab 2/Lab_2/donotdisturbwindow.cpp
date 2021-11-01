#include "donotdisturbwindow.h"
#include "ui_donotdisturbwindow.h"
#include <QMessageBox>

DoNotDisturbWindow::DoNotDisturbWindow(QPair<QTime, QTime>& timePoints, QWidget *parent) :
    QDialog(parent),
    toSet(timePoints),
    ui(new Ui::DoNotDisturbWindow)
{
    ui->setupUi(this);
    setWindowTitle("Do not disturb mode");
    ui->disturbModeStart->setTime(timePoints.first);
    ui->disturbModeEnd->setTime(timePoints.second);
}

void DoNotDisturbWindow::setDoNotDisturbTimePoints()
{
    toSet.first  = ui->disturbModeStart->time();
    toSet.second = ui->disturbModeEnd->time();
}

DoNotDisturbWindow::~DoNotDisturbWindow()
{
    delete ui;
}

void DoNotDisturbWindow::on_pushButton_clicked()
{
    if(ui->disturbModeEnd->time() <= ui->disturbModeStart->time()){
        QMessageBox::QMessageBox::warning(this, "Warning", "Enter correct time points");
    } else {
        setDoNotDisturbTimePoints();
        close();
    }
}

