#include "Neutrophil.h"


float getOffsetNeutrophil(float angle, AnimationParameters* parameters) {
    return
            sin( (angle+parameters->delta) * parameters->wavePeriod )
            *
            parameters->currentPulsationAspect;
}

void updatePulsationAspectNeutrophil(AnimationParameters* parameters) {
    parameters->currentPulsationAspect =
            parameters->pulsationWaveHeight
            +
            (
              pow(sin( parameters->delta * parameters->pulsationSpeed ), 2)
              +
              pow(sin( parameters->delta * parameters->pulsationSpeed * 4), 4)
            )
            *
            parameters->pulsationSpan;
}

Neutrophil::Neutrophil(sf::Vector2f center, float radius, int pointsCount, sf::Color color):
        Cell(center, radius, pointsCount, color) {
    Animation = {
        getOffsetNeutrophil,
        updatePulsationAspectNeutrophil,
        13,
        0.012f,
        1.6f,
        0.024f,
        0.07f,
    };
}
