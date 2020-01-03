#ifndef LSHAPE_H
#define LSHAPE_H

#include "shape.h"
#include "board.h"

class Lshape : public Shape
{
public:
    Lshape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // LSHAPE_H
