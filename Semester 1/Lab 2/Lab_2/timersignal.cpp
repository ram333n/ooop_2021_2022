#include "timersignal.h"
#include "ui_timersignal.h"



//class Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = 0);
//    ~Widget();
//    void play();

//private:
//    QSoundEffect effect;
//};

//Sound::Sound(QWidget *parent) : QWidget(parent){
//    effect.setSource(QUrl::fromLocalFile("sound.wav"));
//    effect.setLoopCount(QSoundEffect::Infinite);
//    effect.setVolume(1.00f);
//}

//void Sound::play(){
//    effect.play();
//}

TimerSignal::TimerSignal(const QString& timerName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerSignal)
{
    ui->setupUi(this);
    QFont font = ui->timerSignalMessage->font();
    font.setPointSize(20);
    font.setBold(true);
    ui->timerSignalMessage->setText("Time for " + timerName + "\n has been expired");
    ui->timerSignalMessage->setFont(font);
    startTimer(1500);
}

void TimerSignal::timerEvent(QTimerEvent* e){
    Q_UNUSED(e);

    QSound::play(":/signal/sounds/sound.wav");
}

TimerSignal::~TimerSignal()
{
    delete ui;
}

void TimerSignal::on_pushButton_clicked()
{
   this->close();
}

