#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape :

            close();

            break;

        case Qt::Key_Space :

            if (_timer.isActive())
                stop();
            else
                start();

            break;
    }
}

void MainWindow::timeout()
{
    if (_time.second() || _time.minute() || _time.hour())
        _time = _time.addSecs(-1);
    else
        setColor(Qt::red);

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
    ui->lcdNumber->setDigitCount(_time.hour() ? 8 : 5);
    ui->lcdNumber->display(_time.toString("hh:mm:ss"));
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
