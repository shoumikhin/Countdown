#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _countDown(true)
    , _showSeconds(true)
{
    ui->setupUi(this);
    update();

    _timer.setInterval(1000);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    stop();
}

void MainWindow::setTime(QTime time)
{
    _time = time;
    stop();
    update();
}

void MainWindow::setCountDown(bool countDown)
{
    _countDown = countDown;
    stop();
    update();
}

void MainWindow::setShowSeconds(bool showSeconds)
{
    _showSeconds = showSeconds;
    stop();
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int j = event->key();

    switch (event->key())
    {
        case Qt::Key_Escape :

            close();

            break;

        case Qt::Key_Space :
        case Qt::Key_Enter :
        case Qt::Key_Return :

            if (_timer.isActive())
                stop();
            else
                start();

            break;
    }
}

void MainWindow::timeout()
{
    if (_countDown)
        if (_time.second() || _time.minute() || _time.hour())
            _time = _time.addSecs(-1);
        else
            setColor(Qt::red);
    else
        _time = _time.addSecs(1);

    update();
}

void MainWindow::start()
{
    _timer.start();
    setColor(Qt::black);
}

void MainWindow::stop()
{
    _timer.stop();
    setColor(Qt::darkBlue);
}

void MainWindow::update()
{
    if (_showSeconds)
    {
        ui->lcdNumber->setDigitCount(_time.hour() ? 8 : 5);
        ui->lcdNumber->display(_time.toString("hh:mm:ss"));
    }
    else
    {
        ui->lcdNumber->setDigitCount(5);
        ui->lcdNumber->display(_time.toString("hh:mm"));
    }
}

void MainWindow::setColor(QColor color)
{
    QPalette palette;

    palette.setColor(QPalette::Foreground, color);
    ui->lcdNumber->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}
