#ifndef TIMERSIGNAL_H
#define TIMERSIGNAL_H

#include <QDialog>

namespace Ui {
class TimerSignal;
}

class TimerSignal : public QDialog
{
    Q_OBJECT

public:
    explicit TimerSignal(QWidget *parent = nullptr);
    ~TimerSignal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TimerSignal *ui;
};

#endif // TIMERSIGNAL_H
