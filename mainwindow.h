#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonOn_clicked();

    void compOff();
    void decTime();
    void zeroingCounterIndication();

    void on_pushButtonClear_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTime *t;
    bool carrentStatusCounter;
    bool stopStatus;
};

#endif // MAINWINDOW_H
