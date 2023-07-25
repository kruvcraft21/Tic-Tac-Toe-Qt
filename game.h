#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QEvent>
#include "gamecell.h"

constexpr unsigned int MAX_CELL = 9;
constexpr unsigned int MAX_SYMBOL_FOR_WIN = 3;

class Game : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *mainLayout;
    QGridLayout *gridGame;
    QLabel *labelPlayer;
    QPalette paletteX {};
    QPalette paletteO {};
    CELL_STATUS mainPlayer;
    uint stepCount;
    bool isFinishGame;

private slots:
    void clear();
    void clickGameCell(GameCell *obj);

signals:
    void cellPressed(GameCell *obj);

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

    void createGrid();
    void createPlayerLabel();
    void createGridButton();

    void switchPlayer();
    void finishMove();

    CELL_STATUS checkThree(int startPos, int max);

    bool checkDig(CELL_STATUS &winer);
    bool checkHorizontal(CELL_STATUS &winer);
    bool checkVertical(CELL_STATUS &winer);

    void offAllButtons();

public:
    Game(QWidget *parent = nullptr);
    ~Game();
};
#endif // GAME_H
