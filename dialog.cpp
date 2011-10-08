#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , _window(new MainWindow)
{
    ui->setupUi(this);
}

void Dialog::accept()
{
    _window->setTime(ui->timeEdit->time());
    _window->showFullScreen();
}

Dialog::~Dialog()
{
    delete ui;
    delete _window;
}
