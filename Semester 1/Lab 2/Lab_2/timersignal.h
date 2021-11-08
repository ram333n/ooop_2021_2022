#ifndef TIMERSIGNAL_H
#define TIMERSIGNAL_H

#include <QDialog>
#include <QSound>
#include <QDialog>


namespace Ui {
class TimerSignal;
}

//class Sound : public QWidget
//{
//    Q_OBJECT

//public:
//    Sound(QWidget *parent = 0);
//    void play();

//private:
//    QSoundEffect effect;
//};


class TimerSignal : public QDialog
{
    Q_OBJECT

public:
    explicit TimerSignal(const QString& timerName,QWidget *parent = nullptr);
    ~TimerSignal();

private slots:
    void on_pushButton_clicked();

    void timerEvent(QTimerEvent* e);

private:
    Ui::TimerSignal *ui;
};

#endif // TIMERSIGNAL_H
