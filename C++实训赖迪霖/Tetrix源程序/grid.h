#ifndef CELL_H
#define CELL_H

#define GRID_LENGTH 20
#define NUM_OF_GRID 4
#define FIRST_GRID 0
#define SECOND_GRID 1
#define THIRD_GRID 2
#define FOUTH_GRID 3

#define NO_COLOR 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define PURPLE 5
#define CYAN 6
#define ORANGE 7

#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QColor>
#include <QtGlobal>
#include <Qt>

class Grid
{
private:
    int color;
    QPointF position;           //在窗口上的像素位置
    QPoint location;            //在游戏区域中的第几行第几列
    Grid& copy(const Grid&);

public:
    Grid() {}
    Grid(QPoint &, QPointF &, int color = NO_COLOR);

    Grid(const Grid& g) { copy(g); }
    Grid& operator=(const Grid& g) { return copy(g); }

    QPointF& getPosition() { return position; }
    QPoint& getLocation() { return location; }

    int getColor() { return color; }
    void setColor(int);

    QColor drawGridColor() const;
};

#endif // CELL_H
