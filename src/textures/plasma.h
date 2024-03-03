#ifndef ECOSYSTEM_PLASMA_H
#define ECOSYSTEM_PLASMA_H

#include "primaryCell.h"

namespace texture {
    class Plasma : public PrimaryCell {

    public:
        explicit Plasma(sf::Vector2f center = {800, 450}, float radius = 7, int pointCount = 180,
                            sf::Color color = sf::Color::Cyan);

    private:
        float getOffset(const float &angle) const override;

        void updatePulsationAspect() override;
    };
}

#endif //ECOSYSTEM_NEUTROPHIL_H
