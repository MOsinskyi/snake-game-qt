#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "snake.h"
#include "gameaudio.h"

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QFile>
#include <QDataStream>

class GameField : public QWidget
{
    Q_OBJECT
public:
    GameField();

private slots:
    void gameLoopSlot();

signals:
    void changingUserFieldPauseText(QString pauseStatus);
    void changingUserFieldScoreText(QString newScore);

private:
    // Game field size
    enum Size
    {
        Width = 300,
        Height = 300
    };

    // Game speed
    const int timerClockSpeed = 100;

    // Snake single ellips size
    const int snakeElementSize = 10;

    int fieldSizeInSnakeElements;
    int score;
    int bestScore;

    bool onPause;
    bool moveIsBlocked;
    bool isGameOver;

    Snake *snake;
    SnakeElement *food;
    QTimer *gameTimer;
    QRandomGenerator *randomGenerator;
    GameAudio *player;

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void setGameOnPause();
    void endGame();
    void newGame();
    void clearObjects();
    void createFood();
    void loudBestScore();
    void saveBestScore();

    bool checkCollision(SnakeElement *firstObj, SnakeElement *secondObj);
};

#endif // GAMEFIELD_H
