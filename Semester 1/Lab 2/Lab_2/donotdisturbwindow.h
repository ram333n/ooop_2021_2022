#ifndef DONOTDISTURBWINDOW_H
#define DONOTDISTURBWINDOW_H
#include "timer.h"
#include <QDialog>

namespace Ui {
class DoNotDisturbWindow;
}

class DoNotDisturbWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DoNotDisturbWindow(QWidget *parent = nullptr);
    ~DoNotDisturbWindow();

private:
    Ui::DoNotDisturbWindow *ui;
    //QList<Timer*>& timers;
};

#endif // DONOTDISTURBWINDOW_H
