#include <iostream>
#include "cell.h"
#include "random"


Cell::Cell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
        : sf::CircleShape(radius), speed(speed), size(size),
          velocity(0, 0), interval(sf::seconds(5)),
          randomMoveInterval(sf::seconds(2)), color(color), targetPosition(center) {
    setPos(center.x, center.y);
    timer.restart();

    int fontSize = radius * 0.8;
    code.setFillColor(sf::Color::Black);
    code.setCharacterSize(fontSize);
    code.setOrigin(fontSize / 3.f,
                   fontSize / 1.5f);

    code.setString(std::string{(char)(rand() % 31 + '@')});
}

void Cell::setTargetPosition(float windowWidth, float windowHeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0, windowWidth);
    std::uniform_real_distribution<float> disY(0, windowHeight);
    targetPosition = sf::Vector2f(disX(gen), disY(gen));
}

// генерация случайного вектора движения
void Cell::setRandomVelocity() {
    auto angle = static_cast<float>(std::rand() % 360) * 3.14159f / 180.f;
    velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}

void Cell::setPos(float x, float y) {
    setPosition(x, y);
    targetPosition = getPosition();
}

void Cell::reflectionControl() {
    sf::Vector2f pos = getPosition();
    if (pos.x <= -100 || pos.y <= -100 || pos.x >= 1700 || pos.y >= 1000 ||
        (pos.y - 900.f) * (pos.y - 900.f) + (pos.x - 1600.f) * (pos.x - 1600.f) <= 400000) {
        velocity = -1.f * velocity;
    }
}
