#ifndef GAMECELL_H
#define GAMECELL_H

#include <QPushButton>

enum CELL_STATUS : uint
{
    None = 0,
    X,
    O,
};

class GameCell : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(CELL_STATUS stat READ stat WRITE setStat)
public:
    GameCell();
    CELL_STATUS stat() const;
    void setStat(CELL_STATUS newStat);
private:
    CELL_STATUS mStat = None;
};

#endif // GAMECELL_H
