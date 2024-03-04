#include "cell.h"
#include "bodyCell.h"
#include "random"


Cell::Cell(float radius, int size, float speed, sf::Vector2f center, sf::Color color)
        : sf::CircleShape(radius),radius(radius), size(size),  speed(speed), center(center),
          velocity(0, 0), interval(sf::seconds(5)),
          randomMoveInterval(sf::seconds(2)), color(color), targetPosition(center) {
    setPos(center.x, center.y);
    timer.restart();
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
        (pos.y - 900.f) * (pos.y - 900.f) + (pos.x - 1600.f) * (pos.x - 1600.f) <= 400100) {
        //velocity = -1.f * velocity;
        velocity = sf::Vector2f(-1, -1);
        velocity = velocity*speed;
    }
}
