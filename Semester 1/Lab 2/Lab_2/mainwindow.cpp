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
    inputWindow = new InputWindow(timers, idGarbage, currentIndex, ui->listTimersWidget, this);
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
    activeTimersCount = 0;

    for(auto it = idToRemove.rbegin(); it!=idToRemove.rend(); ++it){
        int idx = *it;
        removeTimer(ui->listTimersWidget->item(idx));
    }
    idToRemove.clear();
    int rowsCount = ui->listTimersWidget->count();

    for(int i = 0; i < rowsCount; ){
        QListWidgetItem* listItem = ui->listTimersWidget->item(i);
        if(updateSingleTimer(listItem)){
            rowsCount--;
        } else {
            if(!timers[getIdOfListWidgetItem(listItem)].isPaused()){
                closestTime = std::min(closestTime, timers[getIdOfListWidgetItem(listItem)].getDuration());
                activeTimersCount++;
            }
            i++;
        }
    }
    updateStatusBar(closestTime);
}

bool MainWindow::updateSingleTimer(QListWidgetItem* toUpdate){
    int idx = getIdOfListWidgetItem(toUpdate);

    if(!timers[idx].isTimeExpired()){
        if(!timers[idx].isPaused()){
            timers[idx].updateDuration();            
        }
        QString timerInfo;
        timerInfo = QString::number(idx) + "   " + timers[idx].getInfoAboutTimer();
        toUpdate->setText(timerInfo);
    } else {
        if(!isDoNotDisturbModeNow()){
            TimerSignal* message = new TimerSignal(timers[idx].getName());
            message->setAttribute(Qt::WA_DeleteOnClose);
            message->show();
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
    newStatusBarInfo +="time to closest timer signal: " + (closestTimer != QTime(23,59,59) ? closestTimer.toString("hh:mm:ss") : "-");
    ui->statusbar->showMessage(newStatusBarInfo);
}


void MainWindow::removeTimer(QListWidgetItem* toRemove){
    if(!toRemove){
        return;
    }
    int idx = getIdOfListWidgetItem(toRemove);
    ui->listTimersWidget->removeItemWidget(toRemove);
//    if(!timers[idx].isPaused()){
//        --activeTimersCount;
//    }
    timers.remove(idx);
    idGarbage.push_back(idx);
    delete toRemove;
}

void MainWindow::pauseTimer(QListWidgetItem* toPause){
    if(!toPause){
        return;
    }

    int idx = getIdOfListWidgetItem(toPause);
    timers[idx].pauseTimer();
}

void MainWindow::enableTimer(QListWidgetItem* toEnable){
    if(!toEnable){
        return;
    }

    int idx = getIdOfListWidgetItem(toEnable);
    timers[idx].enableTimer();
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
           QTime::currentTime() <= doNotDisturbModeTimePoints.second;
}

void MainWindow::on_actionRemoveTimer_triggered()
{
    QListWidgetItem* toRemove = ui->listTimersWidget->item(currentRow);
    if(!toRemove){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        toRemove->setHidden(true);
        idToRemove.insert(currentRow);
        currentRow--;
    }
}

void MainWindow::on_actionPauseTimer_triggered()
{
    QListWidgetItem* toPause = ui->listTimersWidget->item(currentRow);
    if(!toPause){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        pauseTimer(toPause);
    }
}


void MainWindow::on_actionEnableTimer_triggered()
{
    QListWidgetItem* toEnable = ui->listTimersWidget->item(currentRow);
    if(!toEnable){
        QMessageBox::warning(this, "Warning", "Timer isn't selected");
    } else {
        enableTimer(toEnable);
    }
}

void MainWindow::on_actionPauseAllTimers_triggered()
{
    for(auto& timer : timers){
        timer.pauseTimer();
    }
}

void MainWindow::on_actionEnableAllTimers_triggered()
{
    for(auto& timer : timers){
        timer.enableTimer();
    }
}

void MainWindow::on_listTimersWidget_itemClicked(QListWidgetItem *item)
{
    if(item){
        currentRow = ui->listTimersWidget->row(item);
    } else {
        currentRow = -1;
    }
}

