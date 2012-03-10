#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QKeyEvent>
#include <QSound>

#include "QTimeUtils.h"

#define COLOR_FG Qt::black
#define COLOR_BG Qt::white
#define COLOR_PAUSED Qt::darkBlue
#define COLOR_FIRING Qt::red
#define COLOR_CLOCK Qt::darkGreen
#define INDICATOR_COLUMN QChar(':')
#define INDICATOR_SPACE QChar(' ')
#define TIMER_INTERVAL 100
#define TIMER_SECOND 1000
#define TIMER_HALF_SECOND (TIMER_SECOND / 2)
#define TIME_TEMPALTE "hh%1mm"
#define TIME_TEMPALTE_LENGTH 5
#define TIME_TEMPALTE_SECONDS "hh%1mm%1ss"
#define TIME_TEMPALTE_SECONDS_LENGTH 8

//==============================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _state(Paused)
    , _countDown(true)
    , _countToTime(true)
    , _showSeconds(true)
    , _playSound(true)
    , _foregroundColor(COLOR_BG)
    , _backgroundColor(COLOR_FG)
    , _timeTemplate(TIME_TEMPALTE_SECONDS)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    paint();

    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    _timer.setInterval(TIMER_INTERVAL);
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    _timer.stop();

    delete ui;
}
//------------------------------------------------------------------------------
void MainWindow::setTime(QTime time)
{
    _time = time;
    _timeOnCounter = _countToTime ? _time - QTime::currentTime() : _time;
    _timeFrozenOnCounter = _timeOnCounter;
}
//------------------------------------------------------------------------------
void MainWindow::setCountDown(bool countDown)
{
    _countDown = countDown;
    setTime(_time);
    pause();
}
//------------------------------------------------------------------------------
void MainWindow::setCountToTime(bool countToTime)
{
    _countToTime = countToTime;
    setTime(_time);
    pause();
}
//------------------------------------------------------------------------------
void MainWindow::setShowClock(bool showClock)
{
    ui->clockLCDNumber->setVisible(showClock);
}
//------------------------------------------------------------------------------
void MainWindow::setShowSeconds(bool showSeconds)
{
    _showSeconds = showSeconds;
    _timeTemplate = _showSeconds ? TIME_TEMPALTE_SECONDS : TIME_TEMPALTE;
}
//------------------------------------------------------------------------------
void MainWindow::invertColors(bool invert)
{
    _foregroundColor = invert ? COLOR_BG : COLOR_FG;
    _backgroundColor = invert ? COLOR_FG : COLOR_BG;

    paint();
}
//------------------------------------------------------------------------------
void MainWindow::setPlaySound(bool sound)
{
     _playSound = sound;
}
//------------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape :

            close();
            event->setAccepted(true);

            break;

        case Qt::Key_Space :
        case Qt::Key_Enter :
        case Qt::Key_Return :

            switch (_state)
            {
                case Paused :

                    start();

                    break;

                case Running :

                    pause();

                    break;

                case Firing :

                    break;
            }

            event->setAccepted(true);

            break;
    }
}
//------------------------------------------------------------------------------
void MainWindow::showEvent(QShowEvent *)
{
    _timer.start();
}
//------------------------------------------------------------------------------
void MainWindow::hideEvent(QHideEvent *)
{
    _timer.stop();
}
//------------------------------------------------------------------------------
void MainWindow::timeout()
{
    static QTime previous_time = QTime::currentTime();
    QTime current_time = QTime::currentTime();

    updateCounter(current_time, previous_time);
    updateClock(current_time);

    previous_time = current_time;
}
//------------------------------------------------------------------------------
void MainWindow::pause()
{
    _timeFrozenOnCounter = _countDown ? _time - QTime::currentTime() : _timeOnCounter;
    _state = Paused;
    paint();
}
//------------------------------------------------------------------------------
void MainWindow::start()
{
    if (_countToTime)
    {
        if (_timeFrozenOnCounter < _time - QTime::currentTime())
        {
            _timeOnCounter.setHMS(0, 0, 0);
            fire();

            return;
        }

        _timeOnCounter = _time - QTime::currentTime();
    }

    _state = Running;
    paint();
}
//------------------------------------------------------------------------------
void MainWindow::fire()
{
    _state = Firing;
    paint();
}
//------------------------------------------------------------------------------
void MainWindow::paint()
{
    QPalette palette;

    palette.setColor(QPalette::Window, _backgroundColor);
    palette.setColor(QPalette::Light, _backgroundColor);
    palette.setColor(QPalette::Dark, _backgroundColor);
    palette.setColor(QPalette::Foreground, _foregroundColor);
    setPalette(palette);

    switch (_state)
    {
        case Paused :

            palette.setColor(QPalette::Foreground, COLOR_PAUSED);

            break;

        case Firing :

            palette.setColor(QPalette::Foreground, COLOR_FIRING);

            break;

        default :

            palette.setColor(QPalette::Foreground, _foregroundColor);
    }

    ui->counterLCDNumber->setPalette(palette);

    palette.setColor(QPalette::Foreground, COLOR_CLOCK);
    ui->clockLCDNumber->setPalette(palette);
}
//------------------------------------------------------------------------------
void MainWindow::updateClock(QTime &currentTime)
{
    ui->clockLCDNumber->display(currentTime.toString(QString(_timeTemplate).arg((currentTime.msec() / TIMER_HALF_SECOND) % 2 ? INDICATOR_SPACE : INDICATOR_COLUMN)));
    ui->clockLCDNumber->setDigitCount(_showSeconds ? TIME_TEMPALTE_SECONDS_LENGTH : TIME_TEMPALTE_LENGTH);
}
//------------------------------------------------------------------------------
void MainWindow::updateCounter(QTime &currentTime, QTime &previousTime)
{
    switch (_state)
    {
        case Paused :

            ui->counterLCDNumber->display(_timeOnCounter.toString(QString(_timeTemplate).arg(INDICATOR_COLUMN)));

        break;

        case Running :

            runStep(currentTime, previousTime);
            ui->counterLCDNumber->display(_timeOnCounter.toString(QString(_timeTemplate).arg((_timeOnCounter.msec() / TIMER_HALF_SECOND) % 2 ? INDICATOR_COLUMN : INDICATOR_SPACE)));

        break;

        case Firing :

            if ((currentTime.msec() / TIMER_HALF_SECOND) % 2)
            {
                if (_playSound)
                    QSound::play("sounds/alarm.wav");

                ui->counterLCDNumber->display("");
            }
            else
                ui->counterLCDNumber->display(_timeOnCounter.toString(QString(_timeTemplate).arg(INDICATOR_COLUMN)));

        break;
    }

    if (0 == _timeOnCounter.hour())
        ui->counterLCDNumber->setDigitCount(TIME_TEMPALTE_LENGTH);
    else
        ui->counterLCDNumber->setDigitCount(_showSeconds ? TIME_TEMPALTE_SECONDS_LENGTH : TIME_TEMPALTE_LENGTH);
}
//------------------------------------------------------------------------------
void MainWindow::runStep(QTime &currentTime, QTime &previousTime)
{
    int time_passed = (currentTime - previousTime).msec();

    if (_countDown)
    {
        if (QTime().msecsTo(_timeOnCounter) <= time_passed)
        {
            fire();

            return;
        }

        time_passed = -time_passed;
    }

    _timeOnCounter = _timeOnCounter.addMSecs(time_passed);
}
//==============================================================================
