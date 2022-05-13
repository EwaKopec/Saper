#include "sapertimer.h"

SaperTimer::SaperTimer(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    ZeroTime = QTime::currentTime();
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SaperTimer::showTime);
    timer->start(0);

    showTime();

    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

void SaperTimer::showTime()
{
    QTime time = QTime::currentTime();
    QTime newTime;
    newTime.setHMS(time.hour() - ZeroTime.hour(),time.minute() - ZeroTime.minute(),time.second() - ZeroTime.second());
    QString text = newTime.toString("mm:ss");
    if ((time.second() % 2) == 0)
         text[2] = ' ';
    display(text);
}

QString SaperTimer::Score()
{
    QTime time = QTime::currentTime();
    QTime newTime;
    newTime.setHMS(time.hour() - ZeroTime.hour(),time.minute() - ZeroTime.minute(),time.second() - ZeroTime.second());
    QString text = newTime.toString("mm:ss");
    if ((time.second() % 2) == 0)
         text[2] = ' ';
   return text;
}
