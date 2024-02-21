#include <cmath>
#include "macrophage.h"


float texture::Macrophage::getOffset(const float &angle) const {
    return
            (
                    powf(sinf((angle + parameters.delta) * parameters.wavePeriod * 3), 1)
                    +
                    powf(sinf((angle + parameters.delta) * parameters.wavePeriod * 1), 2)
            )
            *
            parameters.currentPulsationAspect;
}

void texture::Macrophage::updatePulsationAspect() {
    parameters.currentPulsationAspect =
            parameters.pulsationWaveHeight
            +
            (
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 2), 3)
                    +
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 3), 2)
            )
            *
            parameters.pulsationSpan;
}

texture::Macrophage::Macrophage(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        Cell(center, radius, pointsCount, color) {
    parameters = {
            3,
            0.006f,
            2.5f,
            0.03f,
            0.3f,
    };
}
