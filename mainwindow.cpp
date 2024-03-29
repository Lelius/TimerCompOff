#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    carrentStatusCounter = false;
    stopStatus = false;

    QIcon *icon = new QIcon(":/Icon/compoff.png");
    MainWindow::setWindowIcon(*icon);
    MainWindow::setWindowIconText("TimerCompOff");
    this->statusBar()->setSizeGripEnabled(false);

    t = new QTime();

    analogClock = new AnalogClock(this);
    ui->horizontalLayoutAnalog->addWidget(analogClock);
    connect(this, &MainWindow::updateTime, analogClock, &AnalogClock::updateAnalogClock);

    currentTmr = new QTimer(this);
    currentTmr->start(1000);

    zeroingCounterIndication();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete t;
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
    connect(tmr, &QTimer::timeout, this, &MainWindow::decTime, Qt::UniqueConnection);
    carrentStatusCounter = true;
    tmr->start(1000);
}


void MainWindow::decTime()
{
    *t = t->addSecs(-1);
    ui->labelCounter->setText(t->toString());
    ui->timeEdit->setTime(*t);
    emit updateTime(*t);
    if(t->hour() == 0 && t->minute() == 0 && t->second() == 0)
        compOff();
}


void MainWindow::compOff()
{
    carrentStatusCounter = false;
    tmr->stop();
    ui->labelInfo->setText("Выключение компьютера");

    HANDLE           hToken;
    TOKEN_PRIVILEGES tkp   ;

    ::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken);
    ::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1                   ; // set 1 privilege
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // get the shutdown privilege for this process
    ::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    ExitWindowsEx(EWX_POWEROFF|EWX_FORCE, 0);
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
    zeroingCounterIndication();

    if(carrentStatusCounter == false)
        return;
    tmr->stop();
    tmr->setInterval(0);

    carrentStatusCounter = false;
    ui->labelInfo->setText("Таймер сброшен");
}


void MainWindow::zeroingCounterIndication()
{
    t->setHMS(0, 0, 0);
    ui->timeEdit->setTime(*t);
    ui->labelCounter->setText("∞");
    emit updateTime(*t);
}

void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    emit updateTime(time);
}


