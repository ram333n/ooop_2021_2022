#ifndef TIMER_H
#define TIMER_H
#include <QTime>

enum class TimerType{
    Timer,
    AlarmClock
};

class Timer{
public:
    Timer() = default;
    Timer(TimerType newTimerType, const QTime& finish,const QString& newName);
    void changeStatus();
    long getDuration() const;
    TimerType getTimerType() const;
    bool isPaused() const;
    bool isTimeExpired() const;
    QTime getDurationInQTime() const;
    QString getInfoAboutTimer() const;
    QString getName() const;
    void updateDuration();
private:
    long duration;
    TimerType timerType;
    QString name;
    bool isPaused_;
};

#endif // TIMER_H
