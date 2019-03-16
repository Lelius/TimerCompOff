#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOn_clicked()
{
    if (ui->timeEdit->time().hour() == 0 && ui->timeEdit->time().minute() == 0 && ui->timeEdit->time().second() == 0){
        ui->labelInfo->setText("Дайте хотя бы минуту");
        return;
    }
    ui->labelInfo->setText("Идет отсчет");
    *t = ui->timeEdit->time();
    ui->labelCounter->setText(t->toString());
    connect(tmr, SIGNAL(timeout()), this, SLOT(decTime()));
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
    tmr->stop();
    ui->labelInfo->setText("Выключение компьютера");
}
