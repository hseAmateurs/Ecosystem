#include "cell.h"
#include "random"


Cell::Cell(float radius, int size, float speed, const sf::Color &color, float posX, float posY)
        : sf::CircleShape(radius), speed(speed),
          velocity(0, 0), interval(sf::seconds(5)),
          randomMoveInterval(sf::seconds(2)) {
    setFillColor(color);
    setPos(posX, posY);
    targetPosition = sf::Vector2f(posX, posY);
    timer.restart();
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
