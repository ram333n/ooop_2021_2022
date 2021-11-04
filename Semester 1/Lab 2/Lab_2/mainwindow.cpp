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
    //ui->listTimersWidget->setEditTriggers( QAbstractItemView::DoubleClicked );
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
    std::lock_guard g(mutex); //mb useless
    for(int i = 0, rowsCount = ui->listTimersWidget->count(); i < rowsCount;){
        QListWidgetItem* listItem = ui->listTimersWidget->takeItem(i);
        if(updateSingleTimer(listItem, i)){
            rowsCount--;
        } else {
            if(!timers[getIdOfListWidgetItem(listItem)].isPaused()){
                closestTime = std::min(closestTime, timers[getIdOfListWidgetItem(listItem)].getDurationInQTime());
                activeTimersCount++;
            }
            i++;
        }
    }
    updateStatusBar(closestTime);
}

bool MainWindow::updateSingleTimer(QListWidgetItem* toUpdate, int rowToUpdate){
    int idx = getIdOfListWidgetItem(toUpdate);
    if(!timers[idx].isTimeExpired()){
        if(!timers[idx].isPaused()){
            timers[idx].updateDuration();            
        }
        QString timerInfo;
        timerInfo = QString::number(idx) + "   " + timers[idx].getInfoAboutTimer();
        toUpdate->setText(timerInfo);
        ui->listTimersWidget->insertItem(rowToUpdate, toUpdate);
        if(currentRow > -1){
            ui->listTimersWidget->item(currentRow)->setSelected(true);
        }
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
    newStatusBarInfo +="Time to closest timer signal: " + (closestTimer != QTime(23,59,59) ? closestTimer.toString("hh:mm:ss") : "-");
    ui->statusbar->showMessage(newStatusBarInfo);
}


void MainWindow::removeTimer(QListWidgetItem* toRemove){
    if(!toRemove){
        return;
    }
    //std::shared_guard g(mutex);
    int idx = getIdOfListWidgetItem(toRemove);
    ui->listTimersWidget->removeItemWidget(toRemove);
    if(!timers[idx].isPaused()){
        --activeTimersCount;
    }
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
        removeTimer(toRemove);
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
    qDebug()<<"CURRENT ROW"<<currentRow;
}

