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

    void setTime(QTime time, bool countToTime = false);
    void setCountDown(bool countDown);
    void setShowSeconds(bool showSeconds);
    void setColorPalette(QColor foreground, QColor background);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void timeout();

private :
    QTime timeDifference(QTime end, QTime beginning);
    void start();
    void stop(QColor color);
    void update();
    void setColor(QColor color);

private:
    Ui::MainWindow *ui;
    QTimer _timer;
    QTime _time, _timeLimit;
    bool _countDown;
    bool _countToTime;
    bool _showSeconds;
    QChar _indicator;
};

#endif // MAINWINDOW_H
