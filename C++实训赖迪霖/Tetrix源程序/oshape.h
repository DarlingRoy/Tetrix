#ifndef OSHAPE_H
#define OSHAPE_H

#include "shape.h"
#include "board.h"

class Oshape : public Shape
{
public:
    Oshape(Grid &, Board &);
    virtual void rotate() override;

private:
    virtual void computeRotateCenter() override;
};

#endif // OSHAPE_H
