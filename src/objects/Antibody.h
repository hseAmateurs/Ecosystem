#ifndef ECOSYSTEM_ANTIBODY_H
#define ECOSYSTEM_ANTIBODY_H

#include "cell.h"
#include "../utils/cells.h"
#include "../textures/cellTexture.h"

class Antibody : public Cell {
public:
    Antibody(texture::AnimationParameters animation, float radius, int size, float speed,
                 sf::Vector2f center, sf::Color color)
            : Cell(animation, radius, size,
                   speed,
                   center, color) { setCode(rand() % 31 + '@'); }

    int type() const override { return CellType::ANTI; }

    void drawTexture(sf::RenderWindow &window, sf::Time elapsed) override;
    void antibodyDeath();
    void update(Field &field, sf::Time deltaTime) override;

private:
    sf::Time deathClock=sf::seconds(5);
    sf::Clock deathTimer;
};

#endif //ECOSYSTEM_ANTIBODY_H
