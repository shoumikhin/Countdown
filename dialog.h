#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void accept();

private:
    Ui::Dialog *ui;
    MainWindow *_window;
};

#endif // DIALOG_H
