#include "shape.h"

//初始化一个形状时，需要给出形状的第一个方格
Shape::Shape(Grid& grid, Board& b)
    : board(b)
{
    color = NO_COLOR;

    for(int i = 0; i < NUM_OF_GRID; i++)
    {
        grids[i] = Grid();
    }

    grids[FIRST_GRID] = grid;
    whichPosition = 0;
}

int Shape::getColor()
{
    return color;
}

Grid &Shape::getAGrid(int n)
{
    return grids[n];
}

void Shape::setAGrid(int n, Grid& grid)
{
    grids[n]=grid;
}

void Shape::rotate()
{
    //先要计算出旋转之后形状中4个小方块的位置
    computeRotateCenter();

    //记录玩家按了多少次旋转键
    whichPosition++;
    //每4次旋转为一个周期
    whichPosition = whichPosition % NUMBER_OF_ROTATE_POSITIONS;

    if(isValidPosition(whichPosition))
    {
        for(int n = 0; n < NUM_OF_GRID; n++)
        {
            int x = rotatePositions[whichPosition][n].x();
            int y = rotatePositions[whichPosition][n].y();

            //在board对应的位置上放上shape的4个小方块
            grids[n] = board.getAGrid(x, y);
        }
    }
    else
    {
        whichPosition--;        //如果不能旋转，则旋转次数回到原来的值
    }
}

//判断旋转到的方位是否是有效的,n为旋转的次数
bool Shape::isValidPosition(int n)
{
    //依次判断每一个小方块是否能旋转到这个位置
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        QPoint temp=rotatePositions[n][i];

        int x=temp.x();
        int y=temp.y();

        //旋转到的位置在游戏面板之内，而且不会碰到其他已经在这个面板上的方块
        if(x<0||y<0||x>=MAIN_BOARD_HEIGHT||y>=MAIN_BOARD_WIDTH||board.getAGrid(x,y).getColor()!=NO_COLOR)
        {
            return false;
        }
    }
    return true;
}

//计算出旋转中心的位置
void Shape::computeRotateCenter()
{
    //对于每个不同的形状每一次旋转，形状中第2个小方块的位置不变
    for(int i = 0; i < NUMBER_OF_ROTATE_POSITIONS; i++)
    {
        //形状中第2个小方块旋转到的位置就是原来的位置（以第二个方块作为旋转中心）
        rotatePositions[i][SECOND_GRID] = grids[SECOND_GRID].getLocation();
    }
}

Shape::~Shape()
{

}
