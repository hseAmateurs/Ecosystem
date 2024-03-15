#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

#include "../textures/animations.h"
#include "../textures/cellTexture.h"
#include "../utils/cellTypes.h"
#include "../utils/settings.h"

#include "../core/field.h"
#include "../core/assets.h"

using utils::CellType;
using namespace settings;

class Cell : public sf::CircleShape {
public:
    explicit Cell(const Assets::CellParam &cellParam, const texture::AnimationParameters &animation,
                  const sf::Color &color);

    virtual ~Cell() { };

    void update(Field &field, sf::Time deltaTime, sf::RenderWindow &window);

    CellType type() const { return cellType; }

    // Установка случайного вектора движения + обновление времени
    void setRandomMovement();

    void reflectionControl();

    void setCode(const char new_code) { code.setString(new_code); };

    char getCode() const { return code.getString()[0]; };

    int getSize() const { return size; }

    void kill();

    bool isDead() const { return texture.isDead(); }

    bool isDying() const { return texture.isAnimDying(); }

protected:
    virtual void runScript(Field &field, sf::Time deltaTime) = 0;

    template<class T>
    void updateCollision(std::vector<T *> &cells);

    void normalizeVelocity();

    static float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
        return std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
                         (pos1.y - pos2.y) * (pos1.y - pos2.y));
    }

    float radius;
    int size;
    float speed;

    sf::Vector2f velocity;

    sf::Clock timer;

    const float INF = 30000;

private:
    void initCode();

    CellType cellType;
    sf::Text code;
    sf::Time randomMoveInterval;
    texture::CellTexture texture;
};

template<class T>
void Cell::updateCollision(std::vector<T *> &cells) {
    for (T *&otherCell: cells) {
        if (otherCell == this) continue;
        if (getGlobalBounds().intersects(otherCell->getGlobalBounds())) {
            velocity = (getPosition() - otherCell->getPosition());
            velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
            otherCell->velocity = otherCell->getPosition() - getPosition();
            otherCell->normalizeVelocity();
        }
    }
}

#endif //ECOSYSTEM_CELL_H
