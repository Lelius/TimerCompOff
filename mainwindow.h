#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <windows.h>
#include <analogclock.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateTime(QTime);

private slots:

    void compOff();
    void decTime();
    void zeroingCounterIndication();

    void on_pushButtonOn_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonStop_clicked();

    void on_timeEdit_timeChanged(const QTime &time);

private:
    Ui::MainWindow *ui;
    QTimer *currentTmr;
    QTimer *tmr;
    QTime *t;
    bool carrentStatusCounter;
    bool stopStatus;

    AnalogClock *analogClock;
};

#endif // MAINWINDOW_H
