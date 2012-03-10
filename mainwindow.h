#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

//==============================================================================
namespace Ui
{
    class MainWindow;
}
//==============================================================================
enum CounterState
{
    Paused,
    Running,
    Firing
};
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setTime(QTime);
    void setCountDown(bool);
    void setCountToTime(bool);
    void setShowClock(bool);
    void setShowSeconds(bool);
    void invertColors(bool);
    void setPlaySound(bool);

    void pause();
    void start();
    void fire();

protected:
    void keyPressEvent(QKeyEvent *);
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private slots:
    void timeout();

private :
    void paint();
    void updateClock(QTime &);
    void updateCounter(QTime &, QTime &);
    void runStep(QTime &, QTime &);

private :
    Ui::MainWindow *ui;
    CounterState _state;
    bool _countDown;
    bool _countToTime;
    bool _showSeconds;
    bool _playSound;
    QColor _foregroundColor;
    QColor _backgroundColor;
    QString _timeTemplate;
    QTime _timeOnCounter;
    QTime _timeFrozenOnCounter;
    QTime _time;
    QTimer _timer;
};
//==============================================================================
#endif // MAINWINDOW_H
