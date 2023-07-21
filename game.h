#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <array>

enum CELL_STATUS : uint
{
    None = 0,
    X,
    O,
};

constexpr unsigned int MAX_CELL = 9;
constexpr unsigned int MAX_SYMBOL_FOR_WIN = 3;

class Game : public QWidget
{
    Q_OBJECT

private:
    std::array<CELL_STATUS, 9> gameField;
    QVBoxLayout *mainLayout;
    QGridLayout *gridGame;
    QLabel *labelPlayer;
    QPalette paletteX {};
    QPalette paletteO {};
    CELL_STATUS mainPlayer;
    uint stepCount;
    bool isFinishGame;

private:
    void createGrid();
    void createPlayerLabel();
    void createGridButton();
    void switchPlayer();
    void finishMove();
    CELL_STATUS checkThree(int startPos, int max);
    bool checkDig(CELL_STATUS &winer);
    bool checkHorizontal(CELL_STATUS &winer);
    bool checkVertical(CELL_STATUS &winer);

public:
    Game(QWidget *parent = nullptr);
    ~Game();
};
#endif // GAME_H
