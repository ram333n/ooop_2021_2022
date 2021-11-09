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

void Timer::enableTimer(){
    isPaused_ = false;
}

void Timer::pauseTimer(){
    if(timerType==TimerType::Timer){
        isPaused_ = true;
    }
}

QTime Timer::getDuration() const {
    return QTime(0,0,0).addSecs(duration);
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


QString Timer::getName() const {
    return name;
}

QString Timer::getInfoAboutTimer() const {
    QString result;
    result += timerType == TimerType::Timer ? "T" : "A";
    result += "   ";
    result += getDuration().toString("hh:mm:ss");
    result += "   ";
    result += isPaused() ? "P" : "A";
    result += "    ";
    result += name;
    result += "   ";
    return result;
}
