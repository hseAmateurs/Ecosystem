#ifndef ECOSYSTEM_PATHOGEN_H
#define ECOSYSTEM_PATHOGEN_H


#include "primaryCell.h"

namespace texture {
    class Pathogen : public PrimaryCell {
    public:
        explicit Pathogen(sf::Vector2f center = {800, 450}, float radius = 100, int pointCount = 180,
                          sf::Color color = sf::Color::Red);

    private:
        float getOffset(const float &angle) const override;

        void updatePulsationAspect() override;
    };
}

#endif //ECOSYSTEM_PATHOGEN_H
