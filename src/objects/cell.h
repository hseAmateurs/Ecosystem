#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

#include "../textures/cellTexture.h"
#include "../utils/cellTypes.h"
#include "../utils/settings.h"

#include "../core/field.h"
#include "../core/assets.h"

using utils::CellType;
using namespace settings;

class Cell : public sf::CircleShape {
public:
    explicit Cell(Assets::CellParam &cellParam, sf::Vector2f &position);

    void update(Field &field, sf::Time deltaTime, sf::RenderWindow &window);

    CellType type() const { return cellType; }

    // Установка случайного вектора движения + обновление времени
    void setRandomMovement();

    void reflectionControl();

    void setCode(const char new_code) { code.setString(std::string{new_code}); };

    char getCode() const { return code.getString()[0]; };

    int getSize() const { return size; }

    bool isDead() const { return texture.isDead(); }

    bool isDying() const { return texture.isAnimDying(); }

protected:
    virtual void runScript(Field &field, sf::Time deltaTime) = 0;

    template<class T>
    void updateCollision(std::vector<T *> &cells);

    void normalizeVelocity();

    void kill() { texture.startDying(); }

    float radius;
    int size;
    float speed;

    sf::Text code;

    sf::Vector2f velocity;

    sf::Clock timer;

    texture::CellTexture texture;

private:
    void initCode();

    CellType cellType;
    sf::Time randomMoveInterval;
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
