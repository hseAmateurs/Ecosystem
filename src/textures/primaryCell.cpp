#include <cmath>
#include "primaryCell.h"


float texture::PrimaryCell::getOffset(const float& angle) const {
    return
            sinf((angle + parameters.delta) * parameters.wavePeriod)
            *
            parameters.currentPulsationAspect;
}

void texture::PrimaryCell::updatePulsationAspect() {
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

texture::PrimaryCell::PrimaryCell(sf::Vector2f center, float radius, int pointsCount, sf::Color color) :
        center(center), radius(radius), m_vertices(sf::LineStrip, pointsCount + 1), pointsCount(pointsCount),
        color(color) {
    parameters = {
            10,
            0.006f,
            1.6f,
            0.024f,
            0.04f,
    };
    PrimaryCell::update();
}

void texture::PrimaryCell::update() {
    parameters.delta += parameters.rotationSpeed;
    updatePulsationAspect();

    float angle = 0, step = (float)(2 * M_PI / pointsCount);
    float offset;
    for (int i = 0; i <= pointsCount; ++i) {
        sf::Vector2f currentRadiusVector = getRadiusVector(angle, radius);
        offset = getOffset(angle);
        currentRadiusVector *= (1.f + offset);
        m_vertices[i].position = currentRadiusVector + center;
        m_vertices[i].color = color;
        angle += step;
    }
}

void texture::PrimaryCell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(m_vertices, states);
}

sf::Vector2f texture::PrimaryCell::getRadiusVector(const float& angle, const float& r) const {
    return {r * cosf(angle), r * sinf(angle)};
}
