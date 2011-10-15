#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , _window(new MainWindow(parent))
    , _colorDialog(new QColorDialog(parent))
{
    ui->setupUi(this);

    connect(ui->options, SIGNAL(toggled(bool)), this, SLOT(changePalette(bool)));
}

void Dialog::accept()
{
    changePalette(ui->options->isChecked());
    _window->setCountDown(ui->countdown->isChecked());
    _window->setShowSeconds(ui->seconds->isChecked());
    _window->setTime(ui->timeEdit->time(), ui->untilLimit->isChecked());
    _window->showFullScreen();
}

void Dialog::changePalette(bool variant)
{
    if (variant)
        _window->setColorPalette(Qt::white, Qt::black);
    else
        _window->setColorPalette(Qt::black, Qt::white);
}

Dialog::~Dialog()
{
    delete ui;
}
