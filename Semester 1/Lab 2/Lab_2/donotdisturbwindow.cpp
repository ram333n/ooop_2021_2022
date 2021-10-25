#include "donotdisturbwindow.h"
#include "ui_donotdisturbwindow.h"

DoNotDisturbWindow::DoNotDisturbWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoNotDisturbWindow)
    //timers(newTimers)
{
    ui->setupUi(this);
}

DoNotDisturbWindow::~DoNotDisturbWindow()
{
    delete ui;
}
