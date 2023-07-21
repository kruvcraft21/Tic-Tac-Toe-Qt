#include "game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 300);
    setWindowTitle("Tic Tac Toe");

    paletteX.setColor(QPalette::WindowText, Qt::red);
    paletteO.setColor(QPalette::WindowText, Qt::blue);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    QPushButton *tmp = new QPushButton("Начать новую игру");
    tmp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    mainLayout->addWidget(tmp);
    connect(tmp, &QPushButton::clicked, this, [this](){
        delete gridGame;
        delete labelPlayer;
        createGrid();
    });
    createGrid();

}

void Game::createGrid()
{
    gridGame = new QGridLayout;
    mainLayout->addLayout(gridGame);
    createPlayerLabel();
    createGridButton();
}

void Game::createPlayerLabel()
{
    mainPlayer = X;
    stepCount = 0;
    isFinishGame = false;
    labelPlayer = new QLabel("Ходит игрок X");
    QFont font {"Arial Black", 20};
    labelPlayer->setFont(font);
    labelPlayer->setAlignment(Qt::AlignCenter);

    labelPlayer->setPalette(paletteX);
    gridGame->addWidget(labelPlayer, 0, 0, 1, 3);
}

void Game::createGridButton()
{
    QFont font {"Arial Black", 20};
    for (int rowIndex = 1, index = 0; rowIndex < 4; rowIndex++)
    {
        for (int columIndex = 0; columIndex < 3; columIndex++, index++)
        {
            gameField[index] = None;
            QPushButton *tmpButton = new QPushButton(" ");
            tmpButton->setFont(font);
            tmpButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            gridGame->addWidget(tmpButton, rowIndex, columIndex);
            connect(tmpButton, &QPushButton::clicked, [&, tmpButton, &cell = gameField[index]](){
                if (!isFinishGame)
                {
                    switch (this->mainPlayer) {
                        case X:
                            tmpButton->setText("X");
                            cell = X;
                            break;
                        case O:
                            tmpButton->setText("O");
                            cell = O;
                            break;
                    default:
                        break;
                    }
                    stepCount++;
                    tmpButton->setDisabled(true);
                    this->finishMove();
                }
            });
        }
    }
}

CELL_STATUS Game::checkThree(int startPos, int max)
{
    uint sum = 0;
    uint stepSize = (max - startPos) / (MAX_SYMBOL_FOR_WIN - 1);
    for (int i = startPos; i < max; i += stepSize)
    {
        if (gameField[i] == gameField[startPos]) sum++;
    }
    return sum == MAX_SYMBOL_FOR_WIN ? gameField[startPos] : None;
}

bool Game::checkDig(CELL_STATUS &winer)
{
    winer = checkThree(0, 9);
    if (winer != None) return true;

    winer = checkThree(2, 7);
    return winer != None;
}

bool Game::checkHorizontal(CELL_STATUS &winer)
{
    winer = checkThree(0, 3);
    if (winer != None) return true;
    winer = checkThree(3, 6);
    if (winer != None) return true;
    winer = checkThree(6, 9);
    return winer != None;
}

bool Game::checkVertical(CELL_STATUS &winer)
{
    winer = checkThree(0, 7);
    if (winer != None) return true;
    winer = checkThree(1, 8);
    if (winer != None) return true;
    winer = checkThree(2, 9);
    return winer != None;
}

void Game::finishMove()
{
    CELL_STATUS winer = None;
    if (checkDig(winer) || checkHorizontal(winer) || checkVertical(winer))
    {
        isFinishGame = true;
        if (winer == X )
        {
            labelPlayer->setText("Игрок X победил");
        }
        else
        {
            labelPlayer->setText("Игрок O победил");
        }
    }
    else if (stepCount >= MAX_CELL)
    {
        isFinishGame = true;
        labelPlayer->setText("Ничья");
    }
    else
    {
        switchPlayer();
    }
}

void Game::switchPlayer()
{
    if (mainPlayer == X)
    {
        labelPlayer->setText("Ходит игрок O");
        labelPlayer->setPalette(paletteO);
        mainPlayer = O;
    }
    else
    {
        labelPlayer->setText("Ходит игрок X");
        labelPlayer->setPalette(paletteX);
        mainPlayer = X;
    }
}

Game::~Game()
{
}

