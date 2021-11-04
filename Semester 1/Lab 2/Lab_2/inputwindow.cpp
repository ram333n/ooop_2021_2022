#include "inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QHash<int, Timer>& newTimersRef,
                         QQueue<int>& newIdGarbageRef,
                         int& newCurrentIdRef,
                         QListWidget* newListWidget,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputWindow),
    timersRef(newTimersRef),
    listWidget(newListWidget),
    idGarbageRef(newIdGarbageRef),
    currentIdRef(newCurrentIdRef)
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
        int id = -1;;
        if(idGarbageRef.isEmpty()){
            id = currentIdRef;
            ++currentIdRef;
        } else {
            id = idGarbageRef.front();
            idGarbageRef.pop_front();
        }
        TimerType newTimerType = ui->radioButtonTimer->isChecked() ? TimerType::Timer : TimerType::AlarmClock;
        Timer newTimer(newTimerType, ui->inputTimer->time(), ui->lineNameTimerEdit->text());
        listWidget->addItem(QString::number(id) + "   " + newTimer.getInfoAboutTimer());
        timersRef[id] = newTimer;
        qDebug() << timersRef[id].getInfoAboutTimer()<<"Size : "<<timersRef.count();

        close();
    }
}

