#include <cmath>
#include "antibody.h"


float texture::Antibody::getOffset(const float &angle) const {
    return
            (
                    powf(sinf((angle + parameters.delta) * parameters.wavePeriod), 1)
                    //+
                    //(float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 1),2)
            )
            *
            parameters.currentPulsationAspect;
}

void texture::Antibody::updatePulsationAspect() {
    parameters.currentPulsationAspect =
            parameters.pulsationWaveHeight
            +
            (
                    powf(sinf(parameters.delta * parameters.pulsationSpeed * 1), 2)
                    //+
                    //pow(sin( parameters->delta * parameters->pulsationSpeed * 2), 2)
            )
            *
            parameters.pulsationSpan;
}

texture::Antibody::Antibody(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        PrimaryCell(center, radius, pointsCount, color) {
    parameters = {
            3,
            0.015f,
            2.f,
            0.1f,
            0.5f,
    };
}
