#include <cmath>
#include "plasma.h"


float texture::Plasma::getOffset(const float &angle) const {
    return
            sinf((angle + parameters.delta) * parameters.wavePeriod)
            *
            parameters.currentPulsationAspect;
}

void texture::Plasma::updatePulsationAspect() {
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


texture::Plasma::Plasma(sf::Vector2f center, float radius, int pointCount, sf::Color color) :
        PrimaryCell(center, radius, pointCount, color) {
    parameters = {
            13,
            0.008f,
            3.5f,
            0.04f,
            0.1f,
    };
}
