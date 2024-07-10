#include "gamewindow.h"
#include "colormanager.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(Width, Height);

    gameField = new GameField();
    userField = new UserField();
    layout = new QGridLayout();
    centralWidget = new QWidget();

    connect(gameField, &GameField::changingUserFieldPauseText, userField, &UserField::changePauseText);
    connect(gameField, &GameField::changingUserFieldScoreText, userField, &UserField::changeScoreText);

    layout->addWidget(userField, 0, 0);
    layout->addWidget(gameField, 1, 0);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setStyleSheet("background: " + backGroundColor);
}
