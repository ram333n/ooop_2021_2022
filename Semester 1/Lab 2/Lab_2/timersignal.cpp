#include "timersignal.h"
#include "ui_timersignal.h"

TimerSignal::TimerSignal(const QString& timerName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerSignal)
{
    ui->setupUi(this);
    setWindowTitle("Signal");
    QFont font = ui->timerSignalMessage->font();
    font.setPointSize(20);
    font.setBold(true);
    ui->timerSignalMessage->setText("Time for " + timerName + "\n has been expired");
    ui->timerSignalMessage->setFont(font);
    //TODO : sound
}

TimerSignal::~TimerSignal()
{
    delete ui;
}

void TimerSignal::on_pushButton_clicked()
{
   this->close();
}

