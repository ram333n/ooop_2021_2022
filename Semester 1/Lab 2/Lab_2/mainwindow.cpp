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

    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    updateAllTimers();
    updateDoNotDisturbMode();
}


void MainWindow::on_actionAddTimer_triggered()
{
    inputWindow = new InputWindow(timers, currentIndex, ui->listTimersWidget, this);
    inputWindow->setAttribute(Qt::WA_DeleteOnClose);
    inputWindow->show();
}


void MainWindow::on_actionDoNotDisturb_triggered()
{
    doNotDisturbWindow = new DoNotDisturbWindow(doNotDisturbModeTimePoints, this);
    doNotDisturbWindow->setAttribute(Qt::WA_DeleteOnClose);
    doNotDisturbWindow->show();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}


void MainWindow::updateAllTimers(){
    QTime closestTime = QTime(23,59,59);
    QListWidgetItem* listItem;
    activeTimersCount = 0;
    for(int i = 0, rowsCount = ui->listTimersWidget->count(); i < rowsCount;){
        listItem = ui->listTimersWidget->takeItem(i);
        if(updateSingleTimer(i)){
            rowsCount--;
        } else {
            closestTime = std::min(closestTime, timers[getIdOfListWidgetItem(listItem)].getDurationInQTime());
            i++;
            if(!timers[getIdOfListWidgetItem(listItem)].isPaused()){
                activeTimersCount++;
            }
        }
    }
    updateStatusBar(closestTime);
}

bool MainWindow::updateSingleTimer(int idxToUpdate){
    QListWidgetItem* toUpdate = ui->listTimersWidget->item(idxToUpdate);
    int idx = getIdOfListWidgetItem(toUpdate);
    if(!timers[idx].isTimeExpired()){
        if(!timers[idx].isPaused()){
            timers[idx].updateDuration();
        }
        QString timerInfo;
        timerInfo = QString::number(idx) + "   " + timers[idx].getInfoAboutTimer();
        qDebug()<<"TIMER INFO :" <<toUpdate->text();
        toUpdate->setData(Qt::DisplayRole, QVariant(timerInfo));
        toUpdate->setText(timerInfo);
    } else {
        if(!isDoNotDisturbModeNow()){
            TimerSignal* message = new TimerSignal(timers[idx].getName(), this);
            message->setAttribute(Qt::WA_DeleteOnClose);
        }
        removeTimer(toUpdate);
        return true;
    }
    return false;
}

void MainWindow::updateStatusBar(const QTime& closestTimer){
    QString newStatusBarInfo;
    newStatusBarInfo +=activeTimersCount != 0 ? "Active timers : " + QString::number(activeTimersCount) : "No active timers";
    newStatusBarInfo +=", ";
    newStatusBarInfo +="Time to closest timer : " + (closestTimer != QTime(23,59,59) ? closestTimer.toString("hh:mm:ss") : "-");
    ui->statusbar->showMessage(newStatusBarInfo);
}


void MainWindow::removeTimer(QListWidgetItem* toRemove){
    if(!toRemove){
        return;
    }

    int idx = getIdOfListWidgetItem(toRemove);
    ui->listTimersWidget->removeItemWidget(toRemove);
    if(!timers[idx].isPaused()){
        --activeTimersCount;
    }
    timers.remove(idx);
    //delete toRemove; //can bring some problems;
}

void MainWindow::pauseTimer(QListWidgetItem* toPause){
    if(!toPause){
        return;
    }

    int idx = getIdOfListWidgetItem(toPause);
    if(!timers[idx].isPaused()){
        timers[idx].changeStatus();
    }
}

void MainWindow::enableTimer(QListWidgetItem* toEnable){
    if(!toEnable){
        return;
    }

    int idx = getIdOfListWidgetItem(toEnable);
    if(timers[idx].isPaused()){
        timers[idx].changeStatus();
    }
}

int MainWindow::getIdOfListWidgetItem(QListWidgetItem* item) const {
    if(!item){
        return -1;
    }

    int res = 0;
    QString timerInfo = item->text();
    for(int i = 0; timerInfo[i].isDigit(); ++i){
        res = res * 10 + timerInfo[i].digitValue();
    }
    return res;
}


void MainWindow::updateDoNotDisturbMode(){
    if(doNotDisturbModeTimePoints.second < QTime::currentTime()){
        doNotDisturbModeTimePoints.first = doNotDisturbModeTimePoints.second = QTime(0,0,0);
    }
}

bool MainWindow::isDoNotDisturbModeNow() const {
    return doNotDisturbModeTimePoints.first <= QTime::currentTime() &&
           QTime::currentTime() >= doNotDisturbModeTimePoints.second;
}

void MainWindow::on_actionRemoveTimer_triggered()
{
    QListWidgetItem* toRemove = ui->listTimersWidget->currentItem();
    if(!toRemove){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        auto reply = QMessageBox::question(this, "Question", "Do you want to remove selected item?");
        if(reply == QMessageBox::Yes){
            removeTimer(toRemove);
        }
    }
}

void MainWindow::on_actionPauseTimer_triggered()
{
    QListWidgetItem* toPause = ui->listTimersWidget->currentItem();
    if(!toPause){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        pauseTimer(toPause);
    }
}


void MainWindow::on_actionEnableTimer_triggered()
{
    QListWidgetItem* toEnable = ui->listTimersWidget->currentItem();
    if(!toEnable){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        enableTimer(toEnable);
    }
}


void MainWindow::on_actionPauseAllTimers_triggered()
{
    for(int i = 0; i < ui->listTimersWidget->count(); ++i){
        pauseTimer(ui->listTimersWidget->takeItem(i));
    }
}


void MainWindow::on_actionEnableAllTimers_triggered()
{
    for(int i = 0; i < ui->listTimersWidget->count(); ++i){
        enableTimer(ui->listTimersWidget->takeItem(i));
    }
}

