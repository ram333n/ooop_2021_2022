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
