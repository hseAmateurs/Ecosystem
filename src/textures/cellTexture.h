#ifndef ECOSYSTEM_CELLTEXTURE_H
#define ECOSYSTEM_CELLTEXTURE_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "../core/assets.h"

namespace texture {

    struct Birthing {
        Birthing(float birthingSpeed) : birthingSpeed(birthingSpeed) { };

        float getBirthingOffset(sf::Time time) {
            float x = (float)time.asSeconds() * birthingSpeed;
            return x * powf(4, -x + 1);
        }

        bool isEndOfBirthing(sf::Time time) const {
            return (float)time.asSeconds() * birthingSpeed >= 1;
        }

        float birthingSpeed;
    };

    struct Dying {
        // constructor, pointsMultAtExplosion depends on cell type, look at anim{Cell}.cpp -> AnimationParameters init
        Dying(int pointsMultAtExplosion) :
                pointsMultAtExplosion(pointsMultAtExplosion),
                pointsLossSpeed(3.f),
                pointsLoss(35 * pointsMultAtExplosion),
                randomOffsetWidth(2.f),
                explosionWidth(0.01f) { };

        // static functions
        float getDyingOffset(sf::Time time) const {
            float x = (float)time.asSeconds() * pointsLossSpeed;
            return (float)(rand() % 1000) * 0.0001f * randomOffsetWidth + explosionWidth * (x * powf(5, -x + 2));
        };

        // consts
        float pointsLossSpeed;
        float randomOffsetWidth;
        float explosionWidth;
        int pointsMultAtExplosion;


        // dynamic variables
        int pointsLoss;
    };

    struct AnimationParameters {
        // static functions
        float (*getOffset)(float angle, AnimationParameters *parameters);

        void (*updatePulsationAspect)(AnimationParameters *parameters);

        // consts
        int wavePeriod;
        float rotationSpeed;
        float pulsationSpeed;
        float pulsationSpan;
        float pulsationWaveHeight;

        Dying dying;
        Birthing birthing;
        float radiusChangingSpeed;

        // dynamic variables
        float delta;
        float currentPulsationAspect;

        float radiusChangingStep;
        float newRadius;
    };


    class CellTexture : public sf::Drawable, public sf::Transformable {

    public:

        explicit CellTexture(Assets::CellParam &cellParam, int pointsCount = 180)
                :
                parameters(cellParam.animation), radius(cellParam.radius), color(cellParam.color),
                pointsCount(pointsCount + 2),
                m_vertices(sf::TriangleFan, pointsCount + 2),
                rotationDirection(rand() % 2 ? -1 : 1), innerTimer(sf::Time::Zero),
                isDying(false), isBirthing(false), isChangingRadius(false) {
            startBirthing();
        };

        void update(sf::Time elapsed);

        void startDying();

        void startBirthing();

        void changeRadius(float newRadius);

        bool isDead() const { return pointsCount == 0; }

        bool isAnimDying() const { return isDying; }

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void updateDying();

        void updateChangingRadius();

        sf::Vector2f getRadiusVector(const float &angle, const float &radius) const;

        AnimationParameters parameters;
        float radius;
        sf::Color color;

        int pointsCount;
        sf::VertexArray m_vertices;
        int rotationDirection;
        sf::Time innerTimer;

        bool isDying;
        bool isBirthing;
        bool isChangingRadius;
    };
}

#endif //ECOSYSTEM_CELLTEXTURE_H
