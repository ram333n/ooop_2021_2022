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
    explicit DoNotDisturbWindow(QPair<QTime, QTime>& timePoints, QWidget *parent = nullptr);
    ~DoNotDisturbWindow();

private slots:
    void on_pushButton_clicked();

private:
    void setDoNotDisturbTimePoints();
    QPair<QTime, QTime>& toSet;
    Ui::DoNotDisturbWindow *ui;
};

#endif // DONOTDISTURBWINDOW_H
