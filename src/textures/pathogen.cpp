#include <cmath>
#include "pathogen.h"


float texture::Pathogen::getOffset(const float &angle) const {
    return
            (
                    powf(sinf((angle + parameters.delta) * parameters.wavePeriod * 2), 10)
                    +
                    powf(sinf((angle + parameters.delta) * parameters.wavePeriod * 3), 2)
            )
            *
            parameters.currentPulsationAspect;
}

void texture::Pathogen::updatePulsationAspect() {
    parameters.currentPulsationAspect =
            parameters.pulsationWaveHeight
            +
            (
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 3), 2)
                    +
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 2), 2)
            )
            *
            parameters.pulsationSpan;
}


texture::Pathogen::Pathogen(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        PrimaryCell(center, radius, pointsCount, color) {
    parameters = {
            4,
            0.02f,
            2.f,
            0.07f,
            0.1f,
    };
}
