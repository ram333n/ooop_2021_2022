#include "inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QHash<int, Timer>& newTimersRef,
                         int& newId,
                         QListWidget* newListWidget,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputWindow),
    timersRef(newTimersRef),
    listWidget(newListWidget),
    id(newId)
{
    ui->setupUi(this);
    setWindowTitle("Input timer");
}

QString InputWindow::isCorrectInput()
{
    QString errorMessage;

    if(!ui->radioButtonTimer->isChecked()&&!ui->radioButtonAlarmClock->isChecked()){
        errorMessage +="-Select timer type\n";
    }

    if((QTime::currentTime() >=  ui->inputTimer->time() && ui->radioButtonAlarmClock->isChecked())
        ||ui->inputTimer->time()==QTime(0,0,0)) {
        errorMessage +="-Input correct time\n";
    }

    if(ui->lineNameTimerEdit->text().isEmpty() || ui->lineNameTimerEdit->text().size() > 100){
        errorMessage +="-Name of timer is empty or too long\n";
    }

    return errorMessage;
}

InputWindow::~InputWindow()
{
    delete ui;
}

void InputWindow::on_addButton_clicked()
{
    QString errorMessage = isCorrectInput();
    if(!errorMessage.isEmpty()){
        QMessageBox::warning(this, "Warning", errorMessage);
        errorMessage.clear();
    } else {
        TimerType newTimerType = ui->radioButtonTimer->isChecked() ? TimerType::Timer : TimerType::AlarmClock;
        Timer newTimer(newTimerType, ui->inputTimer->time(), ui->lineNameTimerEdit->text());
        listWidget->addItem(QString::number(id) + "   " + newTimer.getInfoAboutTimer());
        timersRef[id] = newTimer;
        id++;
        qDebug() << timersRef[id].getInfoAboutTimer();
        close();
    }
}

