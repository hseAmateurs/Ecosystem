//
// Created by vivan on 20.02.2024.
//


#include "Macrophage.h"

float getOffsetMacrophage(float angle, AnimationParameters* parameters) {
    return
            (
              (float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 3),1)
              +
              (float)pow(sin( (angle+parameters->delta) * parameters->wavePeriod * 1),2)
            )
            *
            parameters->currentPulsationAspect;
}

void updatePulsationAspectMacrophage(AnimationParameters* parameters) {
    parameters->currentPulsationAspect =
            parameters->pulsationWaveHeight
            +
            (
              pow(sin( parameters->delta * parameters->pulsationSpeed * 2), 3)
              +
              pow(sin( parameters->delta * parameters->pulsationSpeed * 3), 2)
            )
            *
            parameters->pulsationSpan;
}

Macrophage::Macrophage(sf::Vector2f center, float radius, int pointsCount, sf::Color color):
        Cell(center, radius, pointsCount, color) {
    Animation = {
        getOffsetMacrophage,
        updatePulsationAspectMacrophage,
        3,
        0.006f,
        2.5f,
        0.03f,
        0.3f,
    };
}