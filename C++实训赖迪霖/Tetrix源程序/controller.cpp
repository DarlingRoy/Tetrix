#include "controller.h"

//mainX和mainYmainBoard在window上的像素位置；nextX和nextY为nextBoard在window上的像素位置
Controller::Controller(int mainX,int mainY,int nextX,int nextY)
    :mainBoard(mainX,mainY,MAIN_BOARD_HEIGHT,MAIN_BOARD_WIDTH),
     nextBoard(nextX,nextY,NEXT_BOARD_HEIGHT,NEXT_BOARD_WIDTH)
{
    //获取当前时间生成随机数种子，用于产生随机数控制随机产生一个方块下落
    QTime time=QTime::currentTime();
    int seed=time.second()*100000+time.msec();
    qsrand(seed);

    passShape=0;
    moveDownOK=true;
    shape=NULL;
}

Board &Controller::getMainBoard()
{
    return mainBoard;
}

Board &Controller::getNextBoard()
{
    return nextBoard;
}

bool Controller::getMoveDownOK()
{
    return moveDownOK;
}

//设置mainBoard上的形状的颜色
void Controller::setShapeColor(int color)
{
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        int x=shape->getAGrid(i).getLocation().x();
        int y=shape->getAGrid(i).getLocation().y();

        //将形参中颜色渲染到mainBoard上
        mainBoard.getAGrid(x,y).setColor(color);
    }
}

void Controller::rotate()
{
    //旋转时，先将形状原来位置的颜色清空，避免干扰判断
    setShapeColor(NO_COLOR);

    shape->rotate();

    //旋转之后重新渲染mainBoard上形状位置的颜色
    setShapeColor(shape->getColor());
}

//在其中一个board上的指定的水平位置hrz和垂直位置vrt上放置一个指定形状的方块
Shape *Controller::placeAShape(Board &bd, int hrz, int vrt, int num)
{
    Shape *shape=NULL;       //声明一个父类的指针，用于实现多态
    switch(num)
    {
    case I_SHAPE:
    {
        QPoint point=bd.getStartLocation(I_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Ishape(firstGrid,bd);
    }
        break;

    case J_SHAPE:
    {
        QPoint point=bd.getStartLocation(J_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Jshape(firstGrid,bd);
    }
        break;

    case L_SHAPE:
    {
        QPoint point=bd.getStartLocation(L_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Lshape(firstGrid,bd);
    }
        break;

    case O_SHAPE:
    {
        QPoint point=bd.getStartLocation(O_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Oshape(firstGrid,bd);
    }
        break;

    case S_SHAPE:
    {
        QPoint point=bd.getStartLocation(S_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Sshape(firstGrid,bd);
    }
        break;

    case T_SHAPE:
    {
        QPoint point=bd.getStartLocation(T_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Tshape(firstGrid,bd);
    }
        break;

    case Z_SHAPE:
    {
        QPoint point=bd.getStartLocation(Z_SHAPE,hrz,vrt);
        Grid firstGrid=bd.getAGrid(point.x(),point.y());
        shape=new Zshape(firstGrid,bd);
    }
        break;

    default:
        break;
    }

    return shape;
}

//放置一个方块到nextBoard
void Controller::nextPlaceAShape()
{
    int randomShape=qrand()%NUM_OF_SHAPES;
    placeAShape(nextBoard,HRZ_CENTER,VRTX_CENTER,randomShape);
    passShape=randomShape;      //用于将当前出现在nextBoard上的形状在下一回合中给到mainBoard
}

//放置一个方块到mainBoard
void Controller::mainPlaceAShape()
{
    moveDownOK=true;

    //先将下落到底部的shape释放掉，放置上去的时候再新声明一个shape
    if(shape!=NULL)
    {
        delete shape;
        shape=NULL;
    }

    shape=placeAShape(mainBoard,HRZ_CENTER,VRTX_START,passShape);
}

void Controller::clearRows()
{
    traverseRows();
}

//返回一次总共消除了多少行
int Controller::numRowsClear()
{
    int n=0;
    traverseRows(&n);
    return n;
}

//遍历所有的行
void Controller::traverseRows(int *rows)
{
    //从下往上依次判断每一行是否是满的
    for(int i=MAIN_BOARD_HEIGHT-1;i>=0;i--)
    {
        if(mainBoard.isFull(i))
        {
            if(rows==NULL)
            {
                mainBoard.clearRow(i);
            }
            else
            {
                ++*rows;
            }
        }
    }
}

//计算分数，每一次消除得到的分数=消除行数的平方
int Controller::computeScore()
{
    int score=numRowsClear();
    return score*score;
}

//消除行时mainBoard整体下降
void Controller::rowsMoveDown()
{
    //定义两个索引
    int pEmpty=MAIN_BOARD_HEIGHT-1; //总是指向空的一行
    int pSomething=pEmpty;          //总是指向有东西的一行

    //从最底一行开始，往上依次判断每一行是否是空的
    for(int i=pEmpty;i>=0;i--)
    {
        //如果第i行是空的
        if(mainBoard.isEmpty(i))
        {
            //把pSomething指向空行的上面一行
            pSomething=i-1;

            //从找到的空行的上面一行开始，往上依次判断每一行是否是空的
            for(int j=pSomething;j>=0;j--)
            {
                if(mainBoard.isSomething(j))
                {
                    //把第j行有东西的行复制粘贴到第i行空行
                    mainBoard.rowCutPaste(j,i);
                    break;
                }
            }
        }
    }
}

//向下移动，调用move函数
void Controller::moveDown()
{
    bool moveable=isMoveable(1,0,true);
    if(moveable)
    {
        move(1,0);
    }
}

//向左移动，调用move函数
void Controller::moveLeft()
{
    bool moveable=isMoveable(0,-1,false);
    if(moveable)
    {
        move(0,-1);
    }
}

//向有移动，调用move函数
void Controller::moveRight()
{
    bool moveable=isMoveable(0,1,false);
    if(moveable)
    {
        move(0,1);
    }
}

//形参中isMoveDown表示方块是否在自然下落的状态中
bool Controller::isMoveable(int upANdDown, int leftAndRight, bool isMoveDown)
{
    bool moveable=false;
    int color=NO_COLOR;

    //先把shape在mainBoard上原来的颜色清空
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        Grid temp=shape->getAGrid(i);
        color=mainBoard.getGridColor(temp);     //把shape原来在mainBoard上位置的颜色存储下来，便于后面不能移动时重新渲染回来
        mainBoard.setGridColor(temp,NO_COLOR);
    }

    //对于形状中的4个小方块，依次算出各个方块移动之后的位置
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        int x=shape->getAGrid(i).getLocation().x();
        int y=shape->getAGrid(i).getLocation().y();

        x+=upANdDown;
        y+=leftAndRight;

        if(x>=0&&x<MAIN_BOARD_HEIGHT&&y>=0&&y<MAIN_BOARD_WIDTH&&mainBoard.getAGrid(x,y).getColor()==NO_COLOR)
        {
            moveable=true;
        }
        else
        {
            //如果自然下落时碰到了底部或者碰到了已经在mainBoard上的其他方块，则不能继续向下移动
            if((x>=MAIN_BOARD_HEIGHT||mainBoard.getAGrid(x,y).getColor()!=NO_COLOR)&&isMoveDown)
            {
                moveDownOK=false;
            }
            moveable=false;
            break;
        }
    }
    //如果不能移动，则把shape原来在mainBoard上的位置重新渲染回来
    if(!moveable)
    {
        for(int i=0;i<NUM_OF_GRID;i++)
        {
            Grid temp=shape->getAGrid(i);
            mainBoard.setGridColor(temp,color);
        }
    }
    return moveable;
}

//实现shape在mainBoard上的移动，第1个形参为1表示向下移动，第2个形参为1表示向右移动，为-1表示向左移动
void Controller::move(int upAndDown, int leftAndRight)
{
    for(int i=0;i<NUM_OF_GRID;i++)
    {
        int x=shape->getAGrid(i).getLocation().x();
        int y=shape->getAGrid(i).getLocation().y();

        //计算出移动后到达的位置
        x+=upAndDown;
        y+=leftAndRight;

        //把shape原来在mainBoard上的颜色复制到移动到的位置上（清除原来位置的颜色已经在判断是否可以移动的函数中实现了）
        Grid temp=mainBoard.getAGrid(x,y);
        shape->setAGrid(i,temp);
        mainBoard.setGridColor(temp,shape->getColor());
    }
}

//判断某种形状的方块是否还能被放在mainBoard上,即是否输掉游戏
bool Controller::canBePlaced()
{
    switch (passShape)
    {
    case I_SHAPE:
    {
        for(int i=0;i<4;i++)
        {
            if(mainBoard.getAGrid(i,MAIN_BOARD_WIDTH/2).getColor()!=NO_COLOR)
                return false;
        }
    }
        break;

    case S_SHAPE:
    {
        for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2+1;j++)
        {
            if(mainBoard.getAGrid(0,j).getColor()!=NO_COLOR)
                return false;
        }
        for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2;j++)
        {
            if(mainBoard.getAGrid(1,j).getColor()!=NO_COLOR)
                return false;
        }
    }
        break;

    case Z_SHAPE:
    {
        for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2+1;j++)
        {
            if(mainBoard.getAGrid(0,j).getColor()!=NO_COLOR)
                return false;
        }
        for(int j=MAIN_BOARD_WIDTH/2;j<=MAIN_BOARD_WIDTH/2+1;j++)
        {
            if(mainBoard.getAGrid(1,j).getColor()!=NO_COLOR)
                return false;
        }
    }
        break;

    case T_SHAPE:
    {
        for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2+1;j++)
        {
            if(mainBoard.getAGrid(0,j).getColor()!=NO_COLOR)
                return false;
        }
        if(mainBoard.getAGrid(1,MAIN_BOARD_WIDTH/2).getColor()!=NO_COLOR)
            return false;
    }
        break;

    case O_SHAPE:
    {
        for(int i=0;i<=1;i++)
            for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2;j++)
                if(mainBoard.getAGrid(i,j).getColor()!=NO_COLOR)
                    return false;
    }
        break;

    case L_SHAPE:
    {
        for(int i=0;i<=2;i++)
            for(int j=MAIN_BOARD_WIDTH/2;j<=MAIN_BOARD_WIDTH/2+1;j++)
                if(mainBoard.getAGrid(i,j).getColor()!=NO_COLOR)
                    return false;
    }
        break;

    case J_SHAPE:
    {
        for(int i=0;i<=2;i++)
            for(int j=MAIN_BOARD_WIDTH/2-1;j<=MAIN_BOARD_WIDTH/2;j++)
                if(mainBoard.getAGrid(i,j).getColor()!=NO_COLOR)
                    return false;
    }
        break;

    default:
        break;
    }
    return true;
}
