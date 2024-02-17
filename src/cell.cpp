#include "cell.h"


Cell::Cell(float radius, int size, float speed, const sf::Color& color, float posX, float posY) : shape(radius), speed(speed)
{
    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(posX, posY);
}