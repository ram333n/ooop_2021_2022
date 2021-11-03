#include "timer.h"

Timer::Timer(TimerType newTimerType, const QTime& finish, const QString& newName){
    name = newName;
    timerType = newTimerType;
    if(timerType == TimerType::Timer){
        duration = finish.hour()*3600 + finish.minute()*60 + finish.second();
    } else {
        duration = QTime::currentTime().secsTo(finish);
    }
    isPaused_ = false;
}

void Timer::changeStatus(){
    isPaused_ = !isPaused_;
}

long Timer::getDuration() const {
    return duration;
}

TimerType Timer::getTimerType() const {
    return timerType;
}

bool Timer::isPaused() const {
    return isPaused_;
}

void Timer::updateDuration(){ //timerEvent
    if(!(isPaused_ && timerType == TimerType::Timer) && !isTimeExpired()){
        --duration;
    }
}

bool Timer::isTimeExpired() const {
    return duration < 1;
}

QTime Timer::getDurationInQTime() const{
    int hours = duration / 3600;
    int mins  = duration / 60 - hours * 60;
    int secs  = duration - hours * 3600 - mins * 60;
    return QTime(hours,mins,secs);
}

QString Timer::getName() const {
    return name;
}

QString Timer::getInfoAboutTimer() const {
    QString result;
    result += timerType == TimerType::Timer ? "T" : "A";
    result += "   ";
    result += getDurationInQTime().toString("hh:mm:ss");
    result += "   ";
    result += isPaused() ? "P" : "A";
    result += "    ";
    result += name;
    result += "   ";
    return result;
}
