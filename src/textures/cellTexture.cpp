#include <cmath>
#include "cellTexture.h"


void texture::CellTexture::update() {
    parameters.delta += rotationDirection * parameters.rotationSpeed;
    parameters.updatePulsationAspect(&parameters);

    float angle = 0, step = (float)(2 * M_PI / pointsCount);
    float offset;

    // look at sf::TriangleFan
    m_vertices[0].position = center;
    m_vertices[0].color = color;
    for (int i = 1; i <= pointsCount + 1; ++i) {
        sf::Vector2f currentRadiusVector = getRadiusVector(angle, radius);
        offset = parameters.getOffset(angle, &parameters);
        currentRadiusVector *= (1.f + offset);
        m_vertices[i].position = currentRadiusVector + center;
        m_vertices[i].color = color;
        angle += step;
    }
}

void texture::CellTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(m_vertices, states);
}

void texture::CellTexture::changeCenter(sf::Vector2f newCenter) {
    center = newCenter;
}

sf::Vector2f texture::CellTexture::getRadiusVector(const float &angle, const float &r) const {
    return {r * cosf(angle), r * sinf(angle)};
}

void texture::CellTexture::setRotationDirection(bool isRight) {
    if (isRight) rotationDirection = 1;
    else rotationDirection = -1;
}
