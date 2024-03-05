#include "cell.h"
#include "random"


Cell::Cell(texture::AnimationParameters animation, float radius, int size, float speed, sf::Vector2f center,
           sf::Color color)
        : sf::CircleShape(radius), speed(speed), size(size), radius(radius), center(center),
          velocity(0, 0), interval(sf::seconds(5)),
          randomMoveInterval(sf::seconds(2)), color(color),
          texture(animation, center, radius, 180, color) {
    setPos(center.x, center.y);
    timer.restart();

    int fontSize = radius * 0.8;
    code.setFillColor(sf::Color::Black);
    code.setCharacterSize(fontSize);
    code.setOrigin(fontSize / 3.f,
                   fontSize / 1.5f);

    setCode(rand() % 31 + '@');
}



// генерация случайного вектора движения
void Cell::setRandomVelocity() {
    auto angle = static_cast<float>(std::rand() % 360) * 3.14159f / 180.f;
    velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}

void Cell::setPos(float x, float y) {
    setPosition(x, y);
}

void Cell::reflectionControl() {
    sf::Vector2f pos = getPosition();
    if (pos.x <= -100 || pos.y <= -100 || pos.x >= 1700 || pos.y >= 1000 ||
        (pos.y - 900.f) * (pos.y - 900.f) + (pos.x - 1600.f) * (pos.x - 1600.f) <= 400100) {
        velocity = sf::Vector2f(-1, -1) * speed;
    }
}
