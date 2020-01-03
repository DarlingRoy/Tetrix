#include"oshape.h"

//O型中的第1个方块为左下角的一个方块
Oshape::Oshape(Grid &grid,Board &bd)
    :Shape(grid,bd)
{
    color=ORANGE;
    int x=grid.getLocation().x();   //x为第几行
    int y=grid.getLocation().y();   //y为第几列

    //用第1个小方块的位置求出其余3个方块在board上的位置
    grids[SECOND_GRID]=bd.getAGrid(x,y+1);
    grids[THIRD_GRID]=bd.getAGrid(x-1,y);
    grids[FOUTH_GRID]=bd.getAGrid(x-1,y+1);

    //将shape中的4个小方格在board上的位置染色，显示出shpae在board上的效果
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        bd.setGridColor(grids[i],color);
    }
}

//因为O型不能旋转，因此函数为空
void Oshape::computeRotateCenter()
{

}

void Oshape::rotate()
{

}
