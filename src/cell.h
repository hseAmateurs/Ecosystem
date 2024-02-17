#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class Cell
{
public:
    Cell(float radius, int size, float speed, const sf::Color& color, float posX, float posY);
    void setPosition(float x, float y) {shape.setPosition(x, y);}
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    //void setRadius(float radius) {shape.setRadius(radius);}
private:
    float speed;
    sf::CircleShape shape;

};






#endif //ECOSYSTEM_CELL_H
