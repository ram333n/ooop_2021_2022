#include "timersignal.h"
#include "ui_timersignal.h"

TimerSignal::TimerSignal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerSignal)
{
    ui->setupUi(this);
}

TimerSignal::~TimerSignal()
{
    delete ui;
}

void TimerSignal::on_pushButton_clicked()
{
    close();
}

