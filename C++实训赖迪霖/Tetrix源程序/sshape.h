#ifndef SSHAPE_H
#define SSHAPE_H

#include "shape.h"
#include "board.h"

class Sshape : public Shape
{
public:
    Sshape(Grid &, Board &);

private:
    virtual void computeRotateCenter() override;
};

#endif // SSHAPE_H
