#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTime *t;
};

#endif // MAINWINDOW_H
