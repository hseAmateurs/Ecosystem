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
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 2), 1)
                    +
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 3), 2)
            )
            *
            parameters.pulsationSpan;
}

texture::Macrophage::Macrophage(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        PrimaryCell(center, radius, pointsCount, color) {
    parameters = {
            3,
            0.005f,
            2.4f,
            0.04f,
            0.3f,
    };
}
