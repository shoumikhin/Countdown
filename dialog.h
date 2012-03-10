#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>

#include "mainwindow.h"

//==============================================================================
namespace Ui
{
    class Dialog;
}
//==============================================================================
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void accept();

private slots:
    void onCountDownButton(bool);
    void onCountToTimeButton(bool);
    void onShowClockButton(bool);
    void onShowSecondsButton(bool);
    void onInvertColorsButton(bool);
    void onSoundButton(bool);

private:
    Ui::Dialog *ui;
    MainWindow *_window;
};
//==============================================================================

#endif // DIALOG_H
