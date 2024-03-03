#include <cmath>
#include "brainCell.h"


float texture::BrainCell::getOffset(const float &angle) const {
    return
            sinf((angle + parameters.delta) * parameters.wavePeriod)
            *
            parameters.currentPulsationAspect;
}

void texture::BrainCell::updatePulsationAspect() {
    parameters.currentPulsationAspect =
            parameters.pulsationWaveHeight
            +
            (
                    powf(sinf(parameters.delta * parameters.pulsationSpeed), 2)
                    +
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 4), 4)
            )
            *
            parameters.pulsationSpan;
}


texture::BrainCell::BrainCell(sf::Vector2f center, float radius, int pointCount, sf::Color color) :
        PrimaryCell(center, radius, pointCount, color) {
    parameters = {
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };
}
