#include "dialog.h"
#include "ui_dialog.h"

//==============================================================================
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , _window(new MainWindow(parent))
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(ui->countDownButton, SIGNAL(toggled(bool)), this, SLOT(onCountDownButton(bool)));
    connect(ui->countToTimeButton, SIGNAL(toggled(bool)), this, SLOT(onCountToTimeButton(bool)));
    connect(ui->showClockButton, SIGNAL(toggled(bool)), this, SLOT(onShowClockButton(bool)));
    connect(ui->showSecondsButton, SIGNAL(toggled(bool)), this, SLOT(onShowSecondsButton(bool)));
    connect(ui->invertColorsButton, SIGNAL(toggled(bool)), this, SLOT(onInvertColorsButton(bool)));
}
//------------------------------------------------------------------------------
void Dialog::accept()
{
    _window->setTime(ui->timeEdit->time());
    _window->showFullScreen();

    if (ui->countToTimeButton->isChecked())
        _window->start();
    else
        _window->pause();
}
//------------------------------------------------------------------------------
void Dialog::onCountDownButton(bool toggled)
{
    _window->setCountDown(toggled);

    if (!toggled)
    {
        ui->countToTimeButton->setChecked(toggled);
        _window->setCountToTime(toggled);
    }
}
//------------------------------------------------------------------------------
void Dialog::onCountToTimeButton(bool toggled)
{
    _window->setCountToTime(toggled);

    if (toggled)
    {
        ui->countDownButton->setChecked(toggled);
        _window->setCountDown(toggled);
    }
}
//------------------------------------------------------------------------------
void Dialog::onShowClockButton(bool toggled)
{
    _window->setShowClock(toggled);
}
//------------------------------------------------------------------------------
void Dialog::onShowSecondsButton(bool toggled)
{
    _window->setShowSeconds(toggled);
}
//------------------------------------------------------------------------------
void Dialog::onInvertColorsButton(bool toggled)
{
    _window->invertColors(toggled);
}
//------------------------------------------------------------------------------
Dialog::~Dialog()
{
    delete ui;
}
//==============================================================================
