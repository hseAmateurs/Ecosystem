#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

//#include "../utils/utils.h"

class Cell : public sf::CircleShape {
public:
    Cell(float radius, int size, float speed, const sf::Color &color, float posX, float posY);

    // Переименовал эту функцию (было setPosition), т.к. она наследуется от CircleShape
    void setPos(float x, float y);

    void setTargetPosition(float windowWidth, float windowHeight);

    template<typename pathogen, typename body, typename macro, typename neutro>
    void update(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                std::vector<neutro> &neutros, sf::Time deltaTime);

    // установка случайного вектора движения
    void setRandomVelocity();

    void reflectionControl();

private:
    template<class T>
    void updateCollision(std::vector<T>& cells);

    float speed;
    sf::Vector2f velocity;
    sf::Vector2f targetPosition;
    sf::Time interval;
    sf::Clock timer;
    sf::Time randomMoveInterval;

};

template<class T>
void Cell::updateCollision(std::vector<T>& cells) {
    for (auto &otherCell : cells) {
        if (&otherCell == this) continue;
        sf::Vector2f otherPosition = otherCell.getPosition();
        sf::Vector2f direction = otherPosition - getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (getGlobalBounds().intersects(otherCell.getGlobalBounds())) {
            velocity = getPosition() - otherCell.getPosition();
            otherCell.velocity = otherCell.getPosition() - getPosition();
        }
    }
}

template<typename pathogen, typename body, typename macro, typename neutro>
void Cell::update(std::vector<pathogen> &pathogens, std::vector<body> &bodies, std::vector<macro> &macroes,
                  std::vector<neutro> &neutros, sf::Time deltaTime) {
    if (timer.getElapsedTime() > randomMoveInterval) {
        setRandomVelocity();
        auto randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
        randomMoveInterval = sf::seconds(randomSeconds);
        timer.restart();
    }
    reflectionControl();
    updateCollision(neutros);
    updateCollision(pathogens);
    updateCollision(bodies);
    updateCollision(macroes);

    move(velocity * deltaTime.asSeconds());
}

#endif //ECOSYSTEM_CELL_H
