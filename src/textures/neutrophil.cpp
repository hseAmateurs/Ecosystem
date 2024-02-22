#include <cmath>
#include "neutrophil.h"


float texture::Neutrophil::getOffset(const float &angle) const {
    return
            sinf((angle + parameters.delta) * parameters.wavePeriod)
            *
            parameters.currentPulsationAspect;
}

void texture::Neutrophil::updatePulsationAspect() {
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


texture::Neutrophil::Neutrophil(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        PrimaryCell(center, radius, pointsCount, color) {
    parameters = {
            13,
            0.012f,
            3.f,
            0.024f,
            0.1f,
    };
}
