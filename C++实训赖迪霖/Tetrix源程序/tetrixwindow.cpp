#include "tetrixwindow.h"

TetrixWindow::TetrixWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameController = new Controller(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());

    //设置固定的时间间隔后重新绘制界面，如固定的时间间隔后方块下落一行
    timer = new QTimer();

    //使用信号和槽机制将各个控件发出的信号与对应的槽函数相连
    connect(ui->btnStart, SIGNAL(clicked(bool)), this, SLOT(startGame()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerStart()));
    connect(ui->btnNew, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(ui->btnPause,SIGNAL(clicked(bool)),this,SLOT(pauseGame()));

    //获取焦点，能让游戏获得玩家的键盘输入
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
}

//按键释放时触发
void TetrixWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if(isStarted)
    {
        switch (key)
        {
        case Qt::Key_Down:
            gameController->moveDown();
            break;

        default:
            break;
        }

        if(gameController->getMoveDownOK())
        {
            switch (key)
            {
            case Qt::Key_Left:
                gameController->moveLeft();
                break;

            case Qt::Key_Right:
                gameController->moveRight();
                break;

            case Qt::Key_Up:
                gameController->rotate();
                update();
                break;

            default:
                break;
            }
        }
    }
    //绘制画面
    update();
}

//绘制画面的事件
void TetrixWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //遍历主游戏区域的每一个小方格
    for(int i=0;i<MAIN_BOARD_HEIGHT;i++)
    {
        for(int j=0;j<MAIN_BOARD_WIDTH;j++)
        {
            //第i行，第j列的一个小方格
            Grid grid=gameController->getMainBoard().getAGrid(i,j);

            //得到小方格在窗口上的位置（像素）
            QPointF position=grid.getPosition();
            QSize size(GRID_LENGTH,GRID_LENGTH);

            //定义一个矩形的绘画区域
            QRectF rect(position,size);
            QColor color=grid.drawGridColor();
            painter.fillRect(rect,color);       //用对应的颜色去填充矩形区域

            //设置形状中每个小方格的边框，显得更有区分度
            int x=position.x();
            int y=position.y();

            //每一个小方块的左边和上边是亮的边界，不显示出线条
            painter.setPen(color.light());
            painter.drawLine(x, y + GRID_LENGTH - 1, x, y);
            painter.drawLine(x, y, x + GRID_LENGTH - 1, y);

            //每一个小方块的右边和下边是暗的边界，显示出线条
            painter.setPen(color.dark());
            painter.drawLine(x + 1, y + GRID_LENGTH - 1,
                             x + GRID_LENGTH - 1, y + GRID_LENGTH - 1);
            painter.drawLine(x + GRID_LENGTH - 1, y + GRID_LENGTH - 1,
                             x + GRID_LENGTH - 1, y + 1);
        }
    }

    //遍历NEXT区域的每一个小方格
    for(int i=0;i<NEXT_BOARD_HEIGHT;i++)
    {
        for(int j=0;j<NEXT_BOARD_WIDTH;j++)
        {
            Grid grid=gameController->getNextBoard().getAGrid(i,j);

            //得到小方格在窗口上的位置（像素）
            QPointF position=grid.getPosition();
            QSize size(GRID_LENGTH,GRID_LENGTH);

            //定义一个矩形的绘画区域
            QRectF rect(position,size);
            QColor color=grid.drawGridColor();
            painter.fillRect(rect,color);

            //设置形状中每个小方格的边框，显得更有区分度
            int x=position.x();
            int y=position.y();

            //每一个小方块的左边和上边是亮的边界，不显示出线条
            painter.setPen(color.light());
            painter.drawLine(x, y + GRID_LENGTH - 1, x, y);
            painter.drawLine(x, y, x + GRID_LENGTH - 1, y);

            //每一个小方块的右边和下边是暗的边界，显示出线条
            painter.setPen(color.dark());
            painter.drawLine(x + 1, y + GRID_LENGTH - 1,
                             x + GRID_LENGTH - 1, y + GRID_LENGTH - 1);
            painter.drawLine(x + GRID_LENGTH - 1, y + GRID_LENGTH - 1,
                             x + GRID_LENGTH - 1, y + 1);
        }
    }
}

int TetrixWindow::timeoutTime()
{
    return 1000/(2+level);
}

//分别在3种情况下开始计时器
void TetrixWindow::timerStart()
{
    //形状在mainBoard中自然下落的情况
    if(gameController->getMoveDownOK())
    {
        gameController->moveDown();
    }
    else
    {
        //消除行时的情况
        if(gameController->numRowsClear() > 0)
        {
            int score = gameController->computeScore();
            score += ui->labelScore->text().toInt();
            level=score/3;
            timer->start(timeoutTime());

            gameController->clearRows();
            gameController->rowsMoveDown();
            ui->labelScore->setText(QString::number(score));
            ui->labelLevel->setText(QString::number(level));
        }
        //一个回合开始的时候        
        if(gameController->canBePlaced())
        {
            gameController->mainPlaceAShape();
            gameController->getNextBoard().clearBoard();
            gameController->nextPlaceAShape();
        }
        else
        {
            gameOver();
        }
    }
    update();
}

void TetrixWindow::startGame()
{
    if(isPaused)
        return;

    level=0;
    timer->start(timeoutTime());

    //游戏开始，在游戏主区域和NEXT区域放置方块
    gameController->mainPlaceAShape();
    gameController->nextPlaceAShape();

    isStarted=true;
    ui->btnStart->setEnabled(false);
    update();
}

void TetrixWindow::pauseGame()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer->stop();
    } else {
        timer->start(timeoutTime());
    }
    update();
}

void TetrixWindow::newGame()
{
    isStarted = false;
    isPaused=false;
    level=0;
    timer->stop();

    delete gameController;
    gameController = NULL;

    gameController = new Controller(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());

    ui->labelScore->setText("0");
    ui->labelLevel->setText("0");
    ui->btnStart->setEnabled(true);

    update();
}

void TetrixWindow::gameOver()
{
    timer->stop();
    isStarted=false;
}

TetrixWindow::~TetrixWindow()
{
    delete ui;
    delete gameController;
    ui = NULL;
    gameController = NULL;
}
