#include "tetrixwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrixWindow w;
    w.show();

    return a.exec();
}
