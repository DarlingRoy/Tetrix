#ifndef ISHAPE_H
#define ISHAPE_H

#include "shape.h"
#include "board.h"

class Ishape : public Shape
{
public:
    Ishape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // ISHAPE_H
