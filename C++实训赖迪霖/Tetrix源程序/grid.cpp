#include "grid.h"

Grid::Grid(QPoint& location, QPointF& position, int color)
{
    this->location = location;
    this->position = position;
    this->color = color;
}

Grid& Grid::copy(const Grid& g)
{
    color = g.color;
    position = g.position;
    location = g.location;

    return *this;
}

void Grid::setColor(int color)
{
    this->color=color;
}

QColor Grid::drawGridColor() const
{
    QColor result;
    switch(color)
    {
    case RED:
        result = QColor("#CC6666");
        break;
    case YELLOW:
        result = QColor("#CCCC66");
        break;
    case BLUE:
        result = QColor("#6666CC");
        break;
    case CYAN:
        result = QColor("#66CCCC");
        break;
    case GREEN:
        result = QColor("#66CC66");
        break;
    case PURPLE:
        result = QColor("#CC66CC");
        break;
    case ORANGE:
        result = QColor("#DAAA00");
        break;
    default:
        result = QColor("transparent");
        break;
    }
    return result;
}
