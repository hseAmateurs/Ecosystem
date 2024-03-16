#include <cmath>
#include "cellTexture.h"


void texture::CellTexture::startDying() {
    isDying = true;
    m_vertices.setPrimitiveType(sf::Points);
    pointsCount *= parameters.dying.pointsMultAtExplosion;
    m_vertices.resize(pointsCount);
    innerTimer = sf::Time::Zero;
}

void texture::CellTexture::startBirthing() {
    isBirthing = true;
    innerTimer = sf::Time::Zero;
}

void texture::CellTexture::updateDying() {
    m_vertices[0].position = center + getRadiusVector(0, radius);
    pointsCount -= parameters.dying.pointsLoss / 5.f;
    m_vertices.resize(pointsCount > 0 ? pointsCount : 0);
}
#include <iostream>

void texture::CellTexture::update(sf::Time elapsed) {
    innerTimer += elapsed;

    parameters.delta += rotationDirection * parameters.rotationSpeed * elapsed.asSeconds();
    parameters.updatePulsationAspect(&parameters);

    float angle = 0, step = (float)(2 * M_PI / (pointsCount - 2));

    m_vertices[0].color = color;
    m_vertices[0].position = center;

    if (isDying)
        updateDying();
    if (isChangingRadius)
        updateChangingRadius();

    for (int i = 1; i < pointsCount; ++i) {
        sf::Vector2f currentRadiusVector = getRadiusVector(angle, radius);
        currentRadiusVector *= 1.f + parameters.getOffset(angle, &parameters);
        if (isDying)
            currentRadiusVector *= 1.f + parameters.dying.getDyingOffset(innerTimer);
        if (isBirthing) {
            if (parameters.birthing.isEndOfBirthing(innerTimer))
                isBirthing = false;
            currentRadiusVector *= parameters.birthing.getBirthingOffset(innerTimer);
        }
        if (isPulsation) {
            if (parameters.pulsation.isEndOfPulsation(innerTimer))
                isPulsation = false;
            currentRadiusVector *= parameters.pulsation.getPulsationOffset(innerTimer);
        }
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

sf::Vector2f texture::CellTexture::getRadiusVector(const float &angle, const float &r) const {
    return {r * cosf(angle), r * sinf(angle)};
}

void texture::CellTexture::changeRadius(float newRadius) {
    innerTimer = sf::Time::Zero;
    isChangingRadius = true;
    parameters.changingRadius.radiusChangingSpan = (newRadius - radius) / radius / 2.f;
    parameters.changingRadius.newRadius = newRadius;
    parameters.changingRadius.oldRadius = radius;
}



void texture::CellTexture::startPulsation() {
    innerTimer = sf::Time::Zero;
    isPulsation = true;
}

void texture::CellTexture::updateChangingRadius() {
    radius = parameters.changingRadius.oldRadius * (parameters.changingRadius.getChangingRadiusOffset(innerTimer) );
    if (parameters.changingRadius.isEndOfChagingRadius(innerTimer)) {
        radius = parameters.changingRadius.newRadius;
        isChangingRadius = false;
    }
}
