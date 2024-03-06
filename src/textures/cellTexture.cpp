#include <cmath>
#include "cellTexture.h"
#include <iostream>



void texture::CellTexture::startDying() {
    isDying = true;
    m_vertices.setPrimitiveType(sf::Points);
    pointsCount *= parameters.dying.pointsMultAtExplosion;
    m_vertices.resize(pointsCount);
    innerTimer = 0;
}

void texture::CellTexture::startBirthing() {
    isBirthing = true;
    innerTimer = 0;
}

void texture::CellTexture::updateDying() {
    m_vertices[0].position = center + getRadiusVector(0, radius);
    if(innerTimer % 5 == 0) {
        pointsCount -= parameters.dying.pointsLoss;
        m_vertices.resize(pointsCount > 0 ? pointsCount : 0);
    }
}


void texture::CellTexture::update() {
    ++innerTimer;

    parameters.delta += rotationDirection * parameters.rotationSpeed;
    parameters.updatePulsationAspect(&parameters);

    float angle = 0, step = (float)(2 * M_PI / (pointsCount-2));

    m_vertices[0].color = color;
    m_vertices[0].position = center;

    if(isDying)
        updateDying();


    for (int i = 1; i < pointsCount; ++i) {
        sf::Vector2f currentRadiusVector = getRadiusVector(angle, radius);
        currentRadiusVector *= 1.f + parameters.getOffset(angle, &parameters);
        if(isDying)
            currentRadiusVector *= 1.f + parameters.dying.getDyingOffset(innerTimer);
        if(isBirthing) {
            if(parameters.birthing.isEndOfBirhing(innerTimer))
                isBirthing = false;
            currentRadiusVector *= parameters.birthing.getBirthingOffset(innerTimer);
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

void texture::CellTexture::changeCenter(sf::Vector2f newCenter) {
    center = newCenter;
}

sf::Vector2f texture::CellTexture::getRadiusVector(const float &angle, const float &r) const {
    return {r * cosf(angle), r * sinf(angle)};
}

void texture::CellTexture::setRotationDirection(bool isRight) {
    rotationDirection = isRight ? 1 : -1;
}
