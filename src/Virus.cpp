#include "Virus.h"


float getOffsetVirus(float angle, AnimationParameters* parameters);
void updatePulsationAspectVirus(AnimationParameters* parameters);

Virus::Virus(sf::Vector2f center, float radius, int pointsCount, sf::Color color):
        Cell(center, radius, pointsCount, color) {
    Animation = {
        getOffsetVirus,
        updatePulsationAspectVirus,
        20,
        0.02f,
        2.f,
        0.07f,
        0.1f,
    };
}

float getOffsetVirus(float angle, AnimationParameters* parameters) {
    return
            (
              (float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 2),5)
              +
              (float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 3),2)
            )
            *
            parameters->currentPulsationAspect;
}
void updatePulsationAspectVirus(AnimationParameters* parameters) {
    parameters->currentPulsationAspect =
            parameters->pulsationWaveHeight
            +
            (
              pow(sin( parameters->delta * parameters->pulsationSpeed * 1), 2)
              +
              pow(sin( parameters->delta * parameters->pulsationSpeed * 2), 2)
            )
            *
            parameters->pulsationSpan;
}
