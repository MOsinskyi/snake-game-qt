#include "snake.h"

SnakeElement::SnakeElement(int x, int y)
{
    this->x = x;
    this->y = y;
}

Snake::Snake()
{
    for(int i = 0; i < startSnakeSize; ++i)
        body.insert(0, new SnakeElement(i, 0));

    direction = SnakeDirection::Down;
}

int Snake::getStartSnakeSize() const { return startSnakeSize; }

SnakeDirection Snake::getDirection() const { return direction; }

void Snake::setDirection(SnakeDirection newDirection)
{
    direction = newDirection;
}

int SnakeElement::getX() const { return x; }

int SnakeElement::getY() const { return y; }

void SnakeElement::setX(int newX)
{
    x = newX;
}

void SnakeElement::setY(int newY)
{
    y = newY;
}
