#include "gamecell.h"

GameCell::GameCell() : QPushButton(" ") {}

CELL_STATUS GameCell::stat() const
{
    return mStat;
}

void GameCell::setStat(CELL_STATUS newStat)
{
    if (newStat != None)
    {
        mStat = newStat;
        switch (mStat) {
        case X:
            setText("X");
            break;
        case O:
            setText("O");
            break;
        default:
            break;
        }
    }
}

