#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "timer.h"
#include "donotdisturbwindow.h"
#include "timersignal.h"
#include "inputwindow.h"

#include <QMainWindow>
#include <QHash>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAddTimer_triggered();

    void on_actionDoNotDisturb_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QHash<int ,Timer> timers;
    QPair<QTime, QTime> doNotDisturbModeTimePoints = {QTime(0,0,0), QTime(0,0,0)};
    int activeTimersCount = 0;
    int currentIndex = 0;

    QTimer* oneSecondTimer;
    InputWindow* inputWindow;
    DoNotDisturbWindow* doNotDisturbWindow;

};
#endif // MAINWINDOW_H
