#include "Headers/gamewindow.h"
#include "Headers/colormanager.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameField = new GameField();
    userField = new UserField();
    layout = new QGridLayout();
    centralWidget = new QWidget();

    setFixedSize(Width, Height);
    setWindowTitle("Snake Game");
    setWindowIcon(QIcon("qrc:/icons/images/windowIcon.png"));

    connect(gameField, &GameField::changingUserFieldPauseText, userField, &UserField::changePauseText);
    connect(gameField, &GameField::changingUserFieldScoreText, userField, &UserField::changeScoreText);

    layout->addWidget(userField, 0, 0);
    layout->addWidget(gameField, 1, 0);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setStyleSheet("background: " + backGroundColor);
}
