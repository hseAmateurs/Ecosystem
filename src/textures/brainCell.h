#ifndef ECOSYSTEM_BRAINCELL_H
#define ECOSYSTEM_BRAINCELL_H

#include "primaryCell.h"

namespace texture {
    class BrainCell : public PrimaryCell {

    public:
        explicit BrainCell(sf::Vector2f center = {800, 450}, float radius = 7, int pointCount = 180,
                            sf::Color color = sf::Color::Cyan);

    private:
        float getOffset(const float &angle) const override;

        void updatePulsationAspect() override;
    };
}

#endif //ECOSYSTEM_NEUTROPHIL_H
