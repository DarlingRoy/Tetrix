#ifndef BOARD_H
#define BOARD_H

#define HRZ_CENTER 0
#define HRZ_START 1
#define VRTX_CENTER 0
#define VRTX_START 1

#define S_O_Z_T_VRTX_START_LOCATION 1
#define I_VRTX_START_LOCATION 3
#define J_L_VRTX_START_LOCATION 2
#define ALL_HRZ_START_LOCATION 0

#define NUM_OF_BOARDS 2
#define MAIN_BOARD 0
#define NEXT_BOARD 1

#define MAIN_BOARD_WIDTH 12
#define MAIN_BOARD_HEIGHT 24

#define NEXT_BOARD_WIDTH 6
#define NEXT_BOARD_HEIGHT 7

#define NUM_OF_SHAPES 7
#define O_SHAPE 0
#define S_SHAPE 1
#define Z_SHAPE 2
#define T_SHAPE 3
#define I_SHAPE 4
#define J_SHAPE 5
#define L_SHAPE 6

#include "grid.h"

//定义一个类board，用于在上面显示方块
class Board
{
private:
    //定义一个一维数组表示board上的小方格。因为有两个不同类型的board，而二维数组需要知道每一行有多少个元素，因此二维数组在这里使用不合适
    Grid* grids;
    int height;
    int width;
    Board& copy(const Board&);

public:
    Board() {  }
    Board(int, int, int, int);
    ~Board();

    Board(const Board& b) { copy(b); }
    Board& operator=(const Board& b) { return copy(b); }

    //获得board上指定行和列的一个方格
    Grid& getAGrid(int, int) const;

    int getGridColor(Grid &);
    void setGridColor(Grid &, int);

    bool isFull(int);
    bool isEmpty(int);
    bool isSomething(int);

    void clearBoard();
    void clearRow(int);
    void rowCutPaste(int, int);

    const QPoint getStartLocation(int, int, int);
};

#endif // BOARD_H
