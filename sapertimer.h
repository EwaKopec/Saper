#ifndef SAPERTIMER_H
#define SAPERTIMER_H

#include <QLCDNumber>
#include <QTimer>
#include <QElapsedTimer>
#include <QTime>


class SaperTimer : public QLCDNumber
{
    Q_OBJECT;
    QTimer* timer;
    //QElapsedTimer *eltimer;
    QTime ZeroTime;

public:
    SaperTimer(QWidget *parent = nullptr);
    QString Score();

private slots:
    void showTime();

};
#endif // SAPERTIMER_H
