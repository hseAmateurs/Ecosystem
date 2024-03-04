#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

class Cell : public sf::CircleShape {
public:
    Cell(float radius, int size, float speed, sf::Vector2f center, sf::Color color);

    // Переименовал эту функцию (было setPosition), т.к. она наследуется от CircleShape
    void setPos(float x, float y);


    template<typename pathogen, typename body, typename macro, typename neutro>
    void update(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime);

    // установка случайного вектора движения
    void setRandomVelocity();
    template<class T>
    void updateCollision(std::vector<T> &cells);
    void reflectionControl();

    // Означает, что эта функция должна быть обязательно переопределена в производных классах
    virtual void drawTexture(sf::RenderWindow &window) = 0;

protected:
    sf::Vector2f velocity;
    float speed;
    sf::Clock timer;
    sf::Time randomMoveInterval=sf::seconds(0);

private:
    sf::Vector2f targetPosition;
    sf::Time interval;

protected:
    float radius;
    int size;
    sf::Color color;
    sf::Vector2f center;

};

template<class T>
void Cell::updateCollision(std::vector<T> &cells) {
    for (auto &otherCell: cells) {
        if (&otherCell == this) continue;
        if (getGlobalBounds().intersects(otherCell.getGlobalBounds())) {
            velocity = (getPosition() - otherCell.getPosition());
            velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
            otherCell.velocity = otherCell.getPosition() - getPosition();
            otherCell.velocity = otherCell.velocity / std::sqrt(
                    otherCell.velocity.x * otherCell.velocity.x + otherCell.velocity.y * otherCell.velocity.y) *
                                 otherCell.speed;
        }
    }
}



#endif //ECOSYSTEM_CELL_H
