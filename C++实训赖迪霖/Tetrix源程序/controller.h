#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "board.h"
#include "grid.h"
#include "shape.h"
#include "oshape.h"
#include "sshape.h"
#include "zshape.h"
#include "tshape.h"
#include "ishape.h"
#include "jshape.h"
#include "lshape.h"

#include <QTime>
#include <QTimer>

//定义一个类用于控制游戏的进行
class Controller
{
private:
    Board mainBoard;
    Board nextBoard;
    int passShape;      //用于保证出现在nextBoard上的形状在下一回合中会出现在mainBoard上
    Shape* shape;       //跟踪现在board上下落的形状
    bool moveDownOK;    //为真表明当前形状正在下落状态中，为假表明已经不能再下落，如碰到底部或其他方块

public:
    Controller(int, int, int, int);

    Board& getMainBoard();
    Board& getNextBoard();

    bool getMoveDownOK();

    void nextPlaceAShape();
    void mainPlaceAShape();
    Shape* placeAShape(Board &, int, int, int);
    void setShapeColor(int);

    void clearRows();
    int numRowsClear();
    void rowsMoveDown();
    void traverseRows(int* rows = NULL);

    void rotate();

    bool isMoveable(int, int, bool);
    void moveDown();
    void moveLeft();
    void moveRight();
    void move(int, int);

    int computeScore();

    bool canBePlaced();
};

#endif // GAME_ENGINE_H
