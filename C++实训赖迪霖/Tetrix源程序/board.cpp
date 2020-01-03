#include "board.h"

//初始化board，将board按行和列划分成多个小方格
//x和y是board上的左上角的那个点在window上的像素位置
Board::Board(int x, int y, int height, int width)
{
    this->height = height;
    this->width = width;

    grids = new Grid[height * width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float w = float(j) * float(GRID_LENGTH) + float(x);
            float h = float(i) * float(GRID_LENGTH) + float(y);

            QPoint location(i, j);
            QPointF position(w, h);

            grids[i * width + j] = Grid(location, position);
        }
    }
}

Board::~Board()
{
    delete[] grids;
    grids = NULL;
}

Board& Board::copy(const Board& b)
{
    height = b.height;
    width = b.width;

    grids = new Grid[height * width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            grids[i * width + j] = b.grids[i * width + j];
        }
    }

    return *this;
}

int Board::getGridColor(Grid& grid)
{
    //计算所求的grid在grids中的索引
    int index = grid.getLocation().x() * width + grid.getLocation().y();
    return grids[index].getColor();
}

void Board::setGridColor(Grid& grid, int color)
{
    int index = grid.getLocation().x() * width + grid.getLocation().y();
    grids[index].setColor(color);
}

//消除nextBoard上的颜色，否则会出现覆盖的效果
void Board::clearBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            grids[i * width + j].setColor(NO_COLOR);
        }
    }
}

//判断形状shape在哪个board上，再获得形状shape中第1个方块的location
const QPoint Board::getStartLocation(int shape, int hrz, int vrt)
{
    int h = 0;
    int w = 0;

    switch (shape)
    {
    case L_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2;
        else
            w=ALL_HRZ_START_LOCATION;
        if (vrt==VRTX_CENTER)
            h=width/2+1;                    //放置在nextBoard上
        else
            h=J_L_VRTX_START_LOCATION;      //放置在mainBoard上
        break;
    case J_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2-1;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2+1;
        else
            h=J_L_VRTX_START_LOCATION;
        break;
    case I_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2+1;
        else
            h=I_VRTX_START_LOCATION;
        break;
    case Z_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2+1;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2;
        else
            h=S_O_Z_T_VRTX_START_LOCATION;
        break;
    case T_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2;
        else
            h=S_O_Z_T_VRTX_START_LOCATION;
        break;
    case S_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2-1;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2;
        else
            h=S_O_Z_T_VRTX_START_LOCATION;
        break;
    case O_SHAPE:
        if(hrz==HRZ_CENTER)
            w=width/2-1;
        else
            w=ALL_HRZ_START_LOCATION;
        if(vrt==VRTX_CENTER)
            h=width/2;
        else
            h=S_O_Z_T_VRTX_START_LOCATION;
        break;
    default:
        break;
    }

    return QPoint(h,w);
}

//返回Board上第i行，第j列的方块
Grid& Board::getAGrid(int i, int j) const
{
    return grids[i * width + j];
}

//判断第n行是否是满的
bool Board::isFull(int n)
{
    //遍历第n行中所有小方格，如果有一个方格的颜色为背景色，则不满
    for(int i=0;i<width;i++)
    {
        if(grids[n*width+i].getColor()==NO_COLOR)
        {
            return false;
        }
    }
    return true;
}

//判断第n行是否为空行
bool Board::isEmpty(int n)
{
    //遍历第n行中所有小方格，如果有一个不是背景色，则不是空行
    for(int i=0;i<width;i++)
    {
        if(grids[n*width+i].getColor()!=NO_COLOR)
        {
            return false;
        }
    }
    return true;
}

//判断第n行是否有东西(但是不满)
bool Board::isSomething(int n)
{
    return (!isEmpty(n) && !isFull(n));
}

//清除第n行
void Board::clearRow(int n)
{
    //遍历第n行中所有小方格，将各个方格的颜色设置为背景色
    for(int i=0;i<width;i++)
    {
        grids[n*width+i].setColor(NO_COLOR);
    }
}

//将第n行各个方块上的颜色给到第m行上对应位置的方块，并将第n行上各个方块的颜色清空
void Board::rowCutPaste(int n, int m)
{
    for(int i = 0; i < width; i++)
    {
        int color = grids[n * width + i].getColor();
        grids[m * width + i].setColor(color);
        grids[n * width + i].setColor(NO_COLOR);
    }
}
