#include "cell.h"
#include "random"
#include <SFML/Graphics.hpp>


Cell::Cell(float radius, int size, float speed, const sf::Color& color, float posX, float posY) : shape(radius), speed(speed), velocity(0,0), interval(sf::seconds(2))
{
    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(posX, posY);
    targetPosition = sf::Vector2f(posX, posY);
    timer.restart();
}

void Cell::setTargetPosition(float windowWidth, float windowHeight)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0, windowWidth);
    std::uniform_real_distribution<float> disY(0, windowHeight);
    targetPosition = sf::Vector2f(disX(gen), disY(gen));
}

void Cell::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    targetPosition = shape.getPosition();
}
