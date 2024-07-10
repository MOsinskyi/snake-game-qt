#ifndef SNAKE_H
#define SNAKE_H

#include <QList>

enum SnakeDirection
{
    Up,
    Left,
    Right,
    Down
};

class SnakeElement
{
public:
    SnakeElement(int x, int y);

    int getX() const;
    int getY() const;

    void setX(int newX);

    void setY(int newY);

private:
    int x, y;
};

class Snake
{
public:
    Snake();
    QList<SnakeElement*> body;

    int getStartSnakeSize() const;

    SnakeDirection getDirection() const;

    void setDirection(SnakeDirection newDirection);

private:
    // Snake size in new game
    const int startSnakeSize = 4;

    SnakeDirection direction;
};


#endif // SNAKE_H
