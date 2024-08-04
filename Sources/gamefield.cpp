#include "Headers/gamefield.h"
#include "Headers/fontmanager.h"
#include "Headers/colormanager.h"

GameField::GameField()
{
    setFixedSize(Width, Height);
    setFocusPolicy(Qt::StrongFocus);

    fieldSizeInSnakeElements = width()/snakeElementSize;

    newGame();
}

void GameField::gameLoopSlot()
{
    SnakeElement *snakeHead;

    int x = snake->body[0]->getX();
    int y = snake->body[0]->getY();

    if (snake->getDirection() == Right)
        snakeHead = new SnakeElement(x + 1, y);
    else if (snake->getDirection() == Left)
        snakeHead = new SnakeElement(x - 1, y);
    else if (snake->getDirection() == Up)
        snakeHead = new SnakeElement(x, y - 1);
    else
        snakeHead = new SnakeElement(x, y + 1);

    if (snakeHead->getX() >= fieldSizeInSnakeElements)
        snakeHead->setX(0);
    else if (snakeHead->getX() < 0)
        snakeHead->setX(fieldSizeInSnakeElements - 1);
    else if (snakeHead->getY() < 0)
        snakeHead->setY(fieldSizeInSnakeElements - 1);
    else if (snakeHead->getY() >= fieldSizeInSnakeElements)
        snakeHead->setY(0);

    for (int i = 0; i < snake->body.size(); ++i){
        if (checkCollision(snakeHead, snake->body[i]))
            endGame();
    }

    // Add score
    if (checkCollision(snakeHead, food)){
        score++;
        createFood();
        player->playEatSound();
        emit changingUserFieldScoreText(QString::number(score));
    } else {
        snake->body.removeLast();
    }

    snake->body.insert(0, snakeHead);
    repaint();
}

void GameField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter canvas;
    QBrush snakeAndTextBrush = QBrush(QColor(objectsColor));
    QBrush appleBrush = QBrush(QColor(appleColor));
    QBrush gameFieldDarkBrickBrush = QBrush(QColor(brickColor));
    QBrush gameFieldLightBrickBrush = QBrush(QColor(backGroundColorRgb));

    canvas.begin(this);
    QPen borderPen, objectsPen;

    borderPen.setStyle(Qt::DashLine);
    objectsPen.setStyle(Qt::SolidLine);

    for (int i = 0; i < fieldSizeInSnakeElements; ++i) {
        for (int j = 0; j < fieldSizeInSnakeElements; ++j){
            QRect gameFieldBrick = QRect(j * snakeElementSize, i * snakeElementSize, snakeElementSize, snakeElementSize);
            if ((i + j) % 2 == 0){
                canvas.setBrush(gameFieldDarkBrickBrush);
                objectsPen.setBrush(gameFieldDarkBrickBrush);
            }
            else{
                canvas.setBrush(gameFieldLightBrickBrush);
                objectsPen.setBrush(gameFieldLightBrickBrush);
            }

            canvas.setPen(objectsPen);
            canvas.drawRect(gameFieldBrick);
        }
    }

    QRect gameField = QRect(0, 0, width()-1, height()-1);
    canvas.setPen(borderPen);
    canvas.setBrush(Qt::NoBrush);
    canvas.drawRect(gameField);

    canvas.setPen(borderPen);
    canvas.setBrush(snakeAndTextBrush);

    // Game Over
    if (isGameOver) {
        canvas.setFont(endGameTextFont);
        canvas.drawText(gameField, Qt::AlignCenter, "Game Over\n\n");
        canvas.setFont(endGameTextFontBestScore);
        canvas.drawText(gameField, Qt::AlignCenter, "Best score: " + QString::number(bestScore));
        clearObjects();
        return;
    }

    canvas.setPen(objectsPen);
    canvas.setBrush(snakeAndTextBrush);

    // Draw snake
    for(int i = 0; i < snake->body.size(); ++i) {
        canvas.drawEllipse(snake->body[i]->getX() * snakeElementSize,
                           snake->body[i]->getY() * snakeElementSize,
                           snakeElementSize,
                           snakeElementSize);
    }

    canvas.setBrush(appleBrush);

    // Draw food
    canvas.drawEllipse(food->getX() * snakeElementSize,
                       food->getY() * snakeElementSize,
                       snakeElementSize, snakeElementSize);

    canvas.end();

    moveIsBlocked = false;
}

void GameField::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space){
        if (isGameOver) {
            newGame();
            return;
        }
        setGameOnPause();
    }

    if (moveIsBlocked) return;

    if (event->key() == Qt::Key_Right && snake->getDirection() != Left)
        snake->setDirection(Right);
    else if (event->key() == Qt::Key_Left && snake->getDirection() != Right)
        snake->setDirection(Left);
    else if (event->key() == Qt::Key_Up && snake->getDirection() != Down)
        snake->setDirection(Up);
    else if (event->key() == Qt::Key_Down && snake->getDirection() != Up)
        snake->setDirection(Down);

    moveIsBlocked = true;
}

void GameField::setGameOnPause()
{
    QString newPauseStatus;

    onPause = !onPause;

    if (onPause) {
        gameTimer->stop();
        newPauseStatus = "Continue";
    } else {
        newPauseStatus = "Pause";
        gameTimer->start(timerClockSpeed);
    }

    emit changingUserFieldPauseText(newPauseStatus);
}

void GameField::endGame()
{
    isGameOver = true;

    if (score > bestScore){
        bestScore = score;
        saveBestScore();
    }

    player->playDeadSound();

    emit changingUserFieldPauseText("New game");

    gameTimer->stop();
    qDebug() << "gameTimerStoped!";
}

void GameField::newGame()
{
    onPause = false;
    moveIsBlocked = false;
    isGameOver = false;
    objectsCleared = false;

    gameTimer = new QTimer;

    snake = new Snake;
    food = new SnakeElement(fieldSizeInSnakeElements/2, fieldSizeInSnakeElements/2);

    randomGenerator = new QRandomGenerator;

    player = new GameAudio;

    score = 0;

    connect(gameTimer, &QTimer::timeout, this, &GameField::gameLoopSlot);

    gameTimer->start(timerClockSpeed);
    qDebug() << "gameTimerStarted...";

    loudBestScore();

    emit changingUserFieldPauseText("Pause");
    emit changingUserFieldScoreText("0");
}

void GameField::clearObjects()
{
    if (objectsCleared) return;

    delete snake;
    delete gameTimer;
    delete food;
    delete randomGenerator;
    objectsCleared = true;

    qDebug() << "Objects deleted";
}

void GameField::createFood()
{
    food->setX(randomGenerator->bounded(fieldSizeInSnakeElements - 1));
    food->setY(randomGenerator->bounded(fieldSizeInSnakeElements - 1));

    for (int i = 0; i < snake->body.size(); ++i) {
        if (checkCollision(food, snake->body[i]))
            return createFood();
    }
}

void GameField::loudBestScore()
{
    QFile file("BestScore.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        bestScore = 0;
        return;
    }

    QDataStream in(&file);
    in >> bestScore;

    file.close();

}

void GameField::saveBestScore()
{
    QFile file("BestScore.txt");
    if (!file.open(QIODevice::WriteOnly)) {
        bestScore = 0;
        return;
    }

    QDataStream out(&file);
    out << bestScore;

    file.close();
}

bool GameField::checkCollision(SnakeElement *firstObj, SnakeElement *secondObj)
{
    return firstObj->getX() == secondObj->getX() && firstObj->getY() == secondObj->getY();
}
