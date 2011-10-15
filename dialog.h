#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>

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

private slots:
    void countdownToggled(bool);
    void untilLimitToggled(bool);
    void changePalette(bool);

private:
    Ui::Dialog *ui;
    MainWindow *_window;
    QColorDialog *_colorDialog;
};

#endif // DIALOG_H
