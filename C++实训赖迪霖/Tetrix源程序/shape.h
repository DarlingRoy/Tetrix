#ifndef SHAPE_H
#define SHAPE_H

#define NUMBER_OF_ROTATE_POSITIONS 4
#define FIRST_POSITION 0
#define SECOND_POSITION 1
#define THIRD_POSITION 2
#define FOUTH_POSITION 3

#include "grid.h"
#include "board.h"

//作为一个基类，各个不同的形状类继承自Shape类
class Shape
{
public:
    Shape(Grid &, Board&);
    virtual ~Shape() = 0;
    int getColor();
    Grid& getAGrid(int);
    void setAGrid(int, Grid&);
    virtual void rotate();

protected:
    int color;
    Grid grids[NUM_OF_GRID];
    Board board;
    int whichPosition;              //用于记录方块旋转的次数

    virtual void computeRotateCenter();
    bool isValidPosition(int);

    //存储第几个方块做第几次旋转之后到达的坐标位置
    QPoint rotatePositions[NUMBER_OF_ROTATE_POSITIONS][NUM_OF_GRID];
};

#endif // SHAPE_H
