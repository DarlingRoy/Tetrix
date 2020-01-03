#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_tetrixwindow.h"
#include "controller.h"
#include "board.h"

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class TetrixWindow : public QMainWindow
{
    Q_OBJECT

public:
    TetrixWindow(QWidget *parent = 0);
    ~TetrixWindow();

    //重写了3个继承自QEvent的事件
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent * event) override;

    void gameOver();
    int timeoutTime();      //设置超时时间间隔

public slots:
    void startGame();
    void timerStart();
    void newGame();
    void pauseGame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Controller* gameController;
    int level;              //记录游戏的难度等级
    bool isStarted;         //判断游戏是否开始了
    bool isPaused;          //判断游戏是否暂停了
};

#endif // MAINWINDOW_H
