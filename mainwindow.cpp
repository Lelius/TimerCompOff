#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    carrentStatusCounter = false;
    stopStatus = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOn_clicked()
{
    if (carrentStatusCounter == true && stopStatus == true)
    {
        stopStatus = false;
        tmr->start();
        ui->labelInfo->setText("Идет отсчет");
        return;
    }
    if (carrentStatusCounter)
        return;
    if (ui->timeEdit->time().hour() == 0 && ui->timeEdit->time().minute() == 0 && ui->timeEdit->time().second() == 0){
        ui->labelInfo->setText("Дайте хотя бы минуту");
        return;
    }
    ui->labelInfo->setText("Идет отсчет");
    *t = ui->timeEdit->time();
    ui->labelCounter->setText(t->toString());
    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(decTime()));
    carrentStatusCounter = true;
    tmr->start(1000);
}

void MainWindow::decTime()
{
    *t = t->addSecs(-1);
    ui->labelCounter->setText(t->toString());
    if(t->hour() == 0 && t->minute() == 0 && t->second() == 0)
        compOff();
}

void MainWindow::compOff()
{
    carrentStatusCounter = false;
    tmr->stop();
    ui->labelInfo->setText("Выключение компьютера");
}

void MainWindow::on_pushButtonStop_clicked()
{
    if(carrentStatusCounter == true){
        tmr->stop();
        stopStatus = true;
        ui->labelInfo->setText("Отсчет остановлен");
    }
}

void MainWindow::on_pushButtonClear_clicked()
{
    tmr->stop();
    tmr->setInterval(0);
    t->setHMS(0, 0, 0);
    ui->timeEdit->setTime(*t);
    ui->labelCounter->setText(t->toString());
    carrentStatusCounter = false;
    ui->labelInfo->setText("Таймер сброшен");
}
