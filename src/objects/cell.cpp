#include <iostream>
#include "cell.h"
#include "random"
#include "../utils/settings.h"

using namespace settings;


Cell::Cell(texture::AnimationParameters animation, float radius, int size, float speed, sf::Vector2f center,
           sf::Color color)
        : sf::CircleShape(radius), speed(speed), size(size), radius(radius), center(center),
          velocity(0, 0), interval(sf::seconds(5)),
          randomMoveInterval(sf::seconds(2)), color(color),
          texture(animation, center, radius, 180, color),
          m_isDead(false) {
    setFillColor(sf::Color::Transparent);
    setOrigin(getRadius(), getRadius());
    setPosition(center);
    timer.restart();
    int fontSize = radius * 0.8;
    code.setFillColor(sf::Color::Black);
    code.setCharacterSize(fontSize);
    code.setOrigin(fontSize / 3.f,
                   fontSize / 1.5f);
}


// генерация случайного вектора движения + обновление времени
void Cell::setRandomMovement() {
    if (timer.getElapsedTime() <= randomMoveInterval) return;

    double angle = (rand() % 360) * M_PI / 180;
    velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;

    auto randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
    randomMoveInterval = sf::seconds(randomSeconds);
    timer.restart();
}

void Cell::reflectionControl() {
    sf::Vector2f pos = getPosition();
    if (pos.x <= -BORDER_OFFSET || pos.x >= SCREEN_WIDTH + BORDER_OFFSET ||
        pos.y <= -BORDER_OFFSET || pos.y >= SCREEN_HEIGHT + BORDER_OFFSET ||
        (pos.y - SCREEN_HEIGHT) * (pos.y - SCREEN_HEIGHT) + (pos.x - SCREEN_WIDTH) * (pos.x - SCREEN_WIDTH) <=
        BRAIN_RADIUS * BRAIN_RADIUS) {
        velocity = sf::Vector2f(-1, -1) * speed;
    }
}

void Cell::normalizeVelocity() {
    velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
}
