#include "cell.h"
#include "CellMath.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>


float getOffsetStaticCell(float angle, AnimationParameters* parameters) {
    return
        sin( (angle+parameters->delta) * parameters->wavePeriod )
        *
        parameters->currentPulsationAspect;
}

void updatePulsationAspectStaticCell(AnimationParameters* parameters) {
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

Cell::Cell(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        center(center), radius(radius), m_vertices(sf::LineStrip, pointsCount+1), pointsCount(pointsCount), color(color) {
    Animation = {
        getOffsetStaticCell,
        updatePulsationAspectStaticCell,
        10,
        0.006f,
        1.6f,
        0.024f,
        0.04f,
    };
    Cell::update(sf::Time::Zero);
}

void Cell::update(sf::Time elapsed) {
    Animation.delta += Animation.rotationSpeed;
    Animation.updatePulsationAspect(&Animation);

    float angle = 0, step = (float) (2*M_PI / pointsCount);
    float offset;
    for (int i = 0; i <= pointsCount; ++i) {
        sf::Vector2f currentRadiusVector = getRadiusVector(angle, radius);
        offset = Animation.getOffset(angle, &Animation);
        currentRadiusVector *= (1.f + offset);
        m_vertices[i].position = currentRadiusVector + center;
        m_vertices[i].color = color;
        angle += step;
    }
}

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(m_vertices, states);
}



