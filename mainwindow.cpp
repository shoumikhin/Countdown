#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QKeyEvent>

namespace
{
QColor FG_COLOR = Qt::black;
QColor BG_COLOR = Qt::white;
QColor PAUSE_COLOR = Qt::darkBlue;
QColor STOP_COLOR = Qt::red;
QChar COLUMN = QChar(':');
QChar SPACE = QChar(' ');
unsigned DELAY = 500;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _countDown(true)
    , _countToTime(false)
    , _showSeconds(true)
    , _indicator(COLUMN)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);

    _timer.setInterval(DELAY);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    stop(PAUSE_COLOR);
}

QTime operator -(QTime const &end, QTime const &beginning)
{
#define SEC_MS  1000
#define MIN_MS  (SEC_MS * 60)
#define HOUR_MS (MIN_MS * 60)
#define DAY_MS  (24 * HOUR_MS)

    int diff = beginning.msecsTo(end);

    if (diff < 0)
        diff = DAY_MS + diff;

    return QTime(diff / HOUR_MS, (diff % HOUR_MS) / MIN_MS, (diff % MIN_MS) / SEC_MS, diff % SEC_MS);

#undef SEC_MS
#undef MIN_MS
#undef HOUR_MS
#undef DAY_MS
}

void MainWindow::setTime(QTime time, bool countToTime)
{
    _countToTime = countToTime;

    if (_countToTime)
    {
        _timeLimit = time;
        _time = _timeLimit - QTime::currentTime();
        start();
    }
    else
    {
        _time = time;
        stop(PAUSE_COLOR);
    }
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

void MainWindow::setColorPalette(QColor foreground, QColor background)
{
    FG_COLOR = foreground;
    BG_COLOR = background;

    QPalette palette;

    palette.setColor(QPalette::Foreground, FG_COLOR);
    palette.setColor(QPalette::Window, BG_COLOR);
    ui->lcdNumber->setPalette(palette);
    setPalette(palette);
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
            {
                if (_countToTime)
                {
                    QTime diff = _timeLimit - QTime::currentTime();

                    if (diff <= _time)
                        _time = diff;
                    else
                    {
                        _time.setHMS(0, 0, 0);
                        stop(STOP_COLOR);
                        _countToTime = false;

                        break;
                    }
                }

                start();
            }

            break;
    }
}

void MainWindow::timeout()
{
    static QTime s_prev_current_time = QTime::currentTime();
    int msecs_spent = (QTime::currentTime() - s_prev_current_time).msec();
    int msecs_overhead = msecs_spent > DELAY ? msecs_spent - DELAY : 0;

    _time = _time.addMSecs(_countDown ? - msecs_overhead : msecs_overhead);

    qDebug("%s.%i", _time.toString().toStdString().c_str(), _time.msec());
    qDebug("%s.%i\n", QTime::currentTime().toString().toStdString().c_str(), QTime::currentTime().msec());

    s_prev_current_time = QTime::currentTime();

    if (COLUMN == _indicator)
    {
        _indicator = SPACE;

        if (_countDown)
            if (_time.second() || _time.minute() || _time.hour())
                _time = _time.addSecs(-1);
            else
            {
                stop(STOP_COLOR);
                _countToTime = false;
            }
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
    setColor(FG_COLOR);
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
