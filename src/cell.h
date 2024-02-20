#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class Cell
{
public:
    Cell(float radius, int size, float speed, const sf::Color& color, float posX, float posY);
    void setPosition(float x, float y);
    void setTargetPosition(float windowWidth, float windowHeight);
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    //void setRadius(float radius) {shape.setRadius(radius);}
    void update(sf::Time deltaTime);
    void setRandomVelocity(); // установка случайного вектора движения
    void reflectionСontrol();
private:
    float speed;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f targetPosition;
    sf::Time interval;
    sf::Clock timer;
    sf::Time randomMoveInterval;

};






#endif //ECOSYSTEM_CELL_H
