#ifndef TSHAPE_H
#define TSHAPE_H

#include "shape.h"
#include "board.h"

class Tshape : public Shape
{
public:
    Tshape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // TSHAPE_H
