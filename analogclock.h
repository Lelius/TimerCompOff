#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>
#include <QTime>
#include <QPainter>

class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = nullptr);
    void updateAnalogClock(QTime);

signals:

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QTime time;
    QTime curTime;
};

#endif // ANALOGCLOCK_H
