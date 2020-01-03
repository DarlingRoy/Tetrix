﻿#include "jshape.h"

//J型的第1个方块是短的直角边上的那一个
Jshape::Jshape(Grid &grid, Board &bd)
    :Shape(grid,bd)
{
    color=GREEN;
    int x=grid.getLocation().x();   //x为第几行
    int y=grid.getLocation().y();   //y为第几列

    //用第1个小方块的位置求出其余3个方块在board上的位置
    grids[SECOND_GRID]=bd.getAGrid(x,y+1);
    grids[THIRD_GRID]=bd.getAGrid(x-1,y+1);
    grids[FOUTH_GRID]=bd.getAGrid(x-2,y+1);

    //将shape中的4个小方格在board上的位置染色，显示出shpae在board上的效果
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        bd.setGridColor(grids[i],color);
    }
}

void Jshape::computeRotateCenter()
{
    //调用父类中的函数
    Shape::computeRotateCenter();

    //因为旋转是以第2个方块为中心，因此先算出第2个方块所在的行和列
    //J型中第2个方块是拐角那个
    int x=rotatePositions[FIRST_POSITION][SECOND_GRID].x(); //第x行
    int y=rotatePositions[FIRST_POSITION][SECOND_GRID].y(); //第y列

    //分别用4个一维数组去存储4个不同方向时4个小方块的位置，按顺时针方向旋转
    //第1个方向
    rotatePositions[FIRST_POSITION][FIRST_GRID]=QPoint(x,y-1);
    rotatePositions[FIRST_POSITION][THIRD_GRID]=QPoint(x-1,y);
    rotatePositions[FIRST_POSITION][FOUTH_GRID]=QPoint(x-2,y);

    //第2个方向
    rotatePositions[SECOND_POSITION][FIRST_GRID]=QPoint(x-1,y);
    rotatePositions[SECOND_POSITION][THIRD_GRID]=QPoint(x,y+1);
    rotatePositions[SECOND_POSITION][FOUTH_GRID]=QPoint(x,y+2);

    //第3个方向
    rotatePositions[THIRD_POSITION][FIRST_GRID]=QPoint(x,y+1);
    rotatePositions[THIRD_POSITION][THIRD_GRID]=QPoint(x+1,y);
    rotatePositions[THIRD_POSITION][FOUTH_GRID]=QPoint(x+2,y);

    //第4个方向
    rotatePositions[FOUTH_POSITION][FIRST_GRID]=QPoint(x+1,y);
    rotatePositions[FOUTH_POSITION][THIRD_GRID]=QPoint(x,y-1);
    rotatePositions[FOUTH_POSITION][FOUTH_GRID]=QPoint(x,y-2);
}
