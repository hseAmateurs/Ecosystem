#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>

#include "../textures/cellTexture.h"
#include "../utils/cellTypes.h"
#include "../utils/settings.h"

#include "../utils/utils.h"

using utils::CellType;
using utils::Field;
using namespace settings;

class Cell : public sf::CircleShape {
public:
    explicit Cell(texture::AnimationParameters texture, float radius, int size, float speed, sf::Vector2f center,
                  sf::Color color);

    // установка случайного вектора движения
    void setRandomVelocity();

    void reflectionControl();

    // Означает, что эта функция должна быть обязательно переопределена в производных классах
    virtual void drawTexture(sf::RenderWindow &window, sf::Time elapsed) = 0;

    void setCode(const char &new_code) { code.setString(new_code); };

    char getCode() const { return code.getString()[0]; };

    void setSize(const int &new_size){ size=new_size; };

    int getSize() const {return size;};

    void setFont(const sf::Font &font) { code.setFont(font); };

    virtual int type() const = 0;

    virtual void update(Field &field, sf::Time deltaTime) = 0;

    texture::CellTexture texture;
protected:
    template<class T>
    void updateCollision(std::vector<T *> &cells);

    sf::Text code;
    float radius;
    int size;
    sf::Color color;
    sf::Vector2f center;
    sf::Vector2f velocity;
    float speed;
    sf::Clock timer;
    sf::Time randomMoveInterval;

private:
    sf::Time interval;
};

template<class T>
void Cell::updateCollision(std::vector<T *> &cells) {
    for (T *&otherCell: cells) {
        if (otherCell == this) continue;
        if (getGlobalBounds().intersects(otherCell->getGlobalBounds())) {
            velocity = (getPosition() - otherCell->getPosition());
            velocity = velocity / std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * speed;
            otherCell->velocity = otherCell->getPosition() - getPosition();
            otherCell->velocity = otherCell->velocity / std::sqrt(
                    otherCell->velocity.x * otherCell->velocity.x + otherCell->velocity.y * otherCell->velocity.y) *
                                  otherCell->speed;
        }
    }
}

#endif //ECOSYSTEM_CELL_H
