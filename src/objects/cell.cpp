#include "cell.h"
#include "random"

using namespace settings;


Cell::Cell(const Assets::CellParam &cellParam, const texture::AnimationParameters &animation,
           const sf::Color &color)
        : sf::CircleShape(cellParam.radius),
          cellType(cellParam.cellType),
          radius(cellParam.radius), size(cellParam.size), speed(cellParam.speed),
          velocity(0, 0),
          randomMoveInterval(sf::seconds(2)),
          texture(animation, color, cellParam) {
    setFillColor(sf::Color::Transparent);
    setOrigin(getRadius(), getRadius());
    timer.restart();

    initCode();
}

void Cell::initCode() {
    int fontSize = radius * 0.8;
    code.setFillColor(sf::Color::Black);
    code.setCharacterSize(fontSize);
    code.setOrigin(fontSize / 3.f,
                   fontSize / 1.5f);
    code.setFont(Assets::instance().font);
    code.setString(' ');
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
    const float brainOffset = 35.f;
    if (pos.x <= -BORDER_OFFSET || pos.x >= SCREEN_WIDTH + BORDER_OFFSET ||
        pos.y <= -BORDER_OFFSET || pos.y >= SCREEN_HEIGHT + BORDER_OFFSET ||
        (pos.y - SCREEN_HEIGHT) * (pos.y - SCREEN_HEIGHT) + (pos.x - SCREEN_WIDTH) * (pos.x - SCREEN_WIDTH) <=
        (BRAIN_RADIUS + brainOffset) * BRAIN_RADIUS + brainOffset) {
        velocity = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) - getPosition();
        normalizeVelocity();
    }
}

void Cell::normalizeVelocity() {
    velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
}

void Cell::update(Field &field, sf::Time deltaTime, sf::RenderWindow &window) {
    runScript(field, deltaTime);

    texture.setPosition(getPosition());
    texture.update(deltaTime);
    window.draw(texture);

    code.setPosition(getPosition());
    window.draw(code);
}

void Cell::kill() {
    if (isDying()) return;
    setCode(' ');
    texture.startDying();
}
