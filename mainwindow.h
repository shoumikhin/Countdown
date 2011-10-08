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
    void setCountDown(bool countDown);
    void setShowSeconds(bool showSeconds);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void timeout();

private :
    void start();
    void stop();
    void update();
    void setColor(QColor color);

private:
    Ui::MainWindow *ui;
    QTimer _timer;
    QTime _time;
    bool _countDown;
    bool _showSeconds;
};

#endif // MAINWINDOW_H
