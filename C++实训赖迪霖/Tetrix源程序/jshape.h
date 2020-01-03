#ifndef JSHAPE_H
#define JSHAPE_H

#include "shape.h"
#include "board.h"

class Jshape : public Shape
{
public:
    Jshape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // JSHAPE_H
