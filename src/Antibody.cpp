//
// Created by vivan on 20.02.2024.
//

#include "Antibody.h"


float getOffsetAntibody(float angle, AnimationParameters* parameters) {
    return
            (
              (float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod),1)
               //+
               //(float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 1),2)
            )
            *
            parameters->currentPulsationAspect;
}

void updatePulsationAspectAntibody(AnimationParameters* parameters) {
    parameters->currentPulsationAspect =
            parameters->pulsationWaveHeight
            +
            (
              pow(sin( parameters->delta * parameters->pulsationSpeed * 1), 2)
              //+
              //pow(sin( parameters->delta * parameters->pulsationSpeed * 2), 2)
            )
            *
            parameters->pulsationSpan;
}

Antibody::Antibody(sf::Vector2f center, float radius, int pointsCount, sf::Color color):
        Cell(center, radius, pointsCount, color) {
    Animation = {
        getOffsetAntibody,
        updatePulsationAspectAntibody,
        3,
        0.015f,
        2.f,
        0.1f,
        0.5f,
    };
}