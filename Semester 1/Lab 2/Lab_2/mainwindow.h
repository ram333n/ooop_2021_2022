#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "timer.h"
#include "donotdisturbwindow.h"
#include "timersignal.h"
#include "inputwindow.h"

#include <QMainWindow>
#include <QHash>
#include <QPair>
#include <QQueue>

#include <shared_mutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent* e);

private slots:
    void on_actionAddTimer_triggered();

    void on_actionDoNotDisturb_triggered();

    void on_actionQuit_triggered();

    void on_actionRemoveTimer_triggered();

    void on_actionPauseTimer_triggered();

    void on_actionEnableTimer_triggered();

    void on_actionPauseAllTimers_triggered();

    void on_actionEnableAllTimers_triggered();

    void on_listTimersWidget_itemClicked(QListWidgetItem *item);

private:
    void updateAllTimers();
    bool updateSingleTimer(QListWidgetItem* toUpdate);
    void updateStatusBar(const QTime& closestTimer);
    void removeTimer(QListWidgetItem* toRemove);
    void pauseTimer(QListWidgetItem* toPause);
    void enableTimer(QListWidgetItem* toEnable);
    int getIdOfListWidgetItem(QListWidgetItem* item) const;
    void updateDoNotDisturbMode();
    bool isDoNotDisturbModeNow() const;

    Ui::MainWindow *ui;
    QHash<int ,Timer> timers;
    QQueue<int> idGarbage;
    QQueue<int> idToRemove;
    QPair<QTime, QTime> doNotDisturbModeTimePoints = {QTime(0,0,0), QTime(0,0,0)};

    int activeTimersCount = 0;
    int currentIndex = 0;
    int currentRow = -1;

    QTimer* oneSecondTimer;
    InputWindow* inputWindow;
    DoNotDisturbWindow* doNotDisturbWindow;

};
#endif // MAINWINDOW_H
