#ifndef ZSHAPE_H
#define ZSHAPE_H

#include "shape.h"
#include "board.h"

class Zshape : public Shape
{
public:
    Zshape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // ZSHAPE_H
