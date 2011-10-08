#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setTime(QTime time);
    void start();
    void stop();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void timeout();

private :
    void update();
    void setColor(QColor color);

private:
    Ui::MainWindow *ui;
    QTimer _timer;
    QTime _time;
};

#endif // MAINWINDOW_H
