#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QKeyEvent>

namespace
{
static QColor RUN_COLOR = Qt::black;
static QColor PAUSE_COLOR = Qt::darkBlue;
static QColor STOP_COLOR = Qt::red;
static QChar COLUMN = QChar(':');
static QChar SPACE = QChar(' ');
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _countDown(true)
    , _showSeconds(true)
    , _indicator(COLUMN)
{
    ui->setupUi(this);

    _timer.setInterval(500);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    stop(PAUSE_COLOR);
}

void MainWindow::setTime(QTime time)
{
    _time = time;
    stop(PAUSE_COLOR);
}

void MainWindow::setCountDown(bool countDown)
{
    _countDown = countDown;
    stop(PAUSE_COLOR);
}

void MainWindow::setShowSeconds(bool showSeconds)
{
    _showSeconds = showSeconds;
    stop(PAUSE_COLOR);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape :

            close();

            break;

        case Qt::Key_Space :
        case Qt::Key_Enter :
        case Qt::Key_Return :

            if (_timer.isActive())
                stop(PAUSE_COLOR);
            else
                start();

            break;
    }
}

void MainWindow::timeout()
{
    if (COLUMN == _indicator)
    {
        _indicator = SPACE;

        if (_countDown)
            if (_time.second() || _time.minute() || _time.hour())
                _time = _time.addSecs(-1);
            else
                stop(STOP_COLOR);
        else
            _time = _time.addSecs(1);
    }
    else
        _indicator = COLUMN;

    update();
}

void MainWindow::start()
{
    _timer.start();
    setColor(RUN_COLOR);
    update();
}

void MainWindow::stop(QColor color)
{
    _timer.stop();
    _indicator = COLUMN;
    setColor(color);
    update();
}

void MainWindow::update()
{
    if (_showSeconds)
    {
        ui->lcdNumber->setDigitCount(_time.hour() ? 8 : 5);
        ui->lcdNumber->display(_time.toString(QString("hh%1mm%1ss").arg(_indicator)));

    }
    else
    {
        ui->lcdNumber->setDigitCount(5);
        ui->lcdNumber->display(_time.toString(QString("hh%1mm").arg(_indicator)));
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
