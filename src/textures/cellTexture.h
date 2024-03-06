#ifndef ECOSYSTEM_CELLTEXTURE_H
#define ECOSYSTEM_CELLTEXTURE_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace texture {

    struct birthing {
        birthing(float birthingSpeed) : birthingSpeed(birthingSpeed) { };

        float getBirthingOffset(int time) {
            float x = (float)time * birthingSpeed;
            return x * powf(4, -x + 1);
        }

        bool isEndOfBirhing(int time) const {
            return (float)time * birthingSpeed >= 1;
        }

        float birthingSpeed;
    };

    struct dying {
        // constructor, pointsMultAtExplosion depends on cell type, look at anim{Cell}.cpp -> AnimationParameters init
        dying(int pointsMultAtExplosion) :
                pointsMultAtExplosion(pointsMultAtExplosion),
                pointsLossSpeed(0.05f),
                pointsLoss(35 * pointsMultAtExplosion),
                randomOffsetWidth(2.f),
                explosionWidth(0.01f) { };

        // static functions
        float getDyingOffset(int time) const {
            float x = (float)time * pointsLossSpeed;
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

        dying dying;
        birthing birthing;

        // dynamic variables
        float delta;
        float currentPulsationAspect;
    };


    class CellTexture : public sf::Drawable, public sf::Transformable {

    public:

        explicit CellTexture(AnimationParameters animation, sf::Vector2f center = {0, 0}, float radius = 15,
                             int pointsCount = 180,
                             sf::Color color = sf::Color::Magenta)
                :
                center(center), radius(radius),
                m_vertices(sf::TriangleFan, pointsCount + 2), pointsCount(pointsCount + 2), color(color),
                parameters(animation),
                isDying(false), isBirthing(false), innerTimer(0) {
            startBirthing();
            setRotationDirection(rand() % 2);
        };

        void update();

        void changeCenter(sf::Vector2f newCenter) { center = newCenter; };

        void startDying();

        void startBirthing();

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void updateDying();

        sf::Vector2f getRadiusVector(const float &angle, const float &radius) const;

        void setRotationDirection(bool isRight) { rotationDirection = isRight ? 1 : -1; };

        AnimationParameters parameters;

        int rotationDirection;

        float radius;
        sf::Vector2f center;
        sf::VertexArray m_vertices;

        int pointsCount;
        sf::Color color;


        bool isDying;
        bool isBirthing;
        int innerTimer;
    };
}

#endif //ECOSYSTEM_CELLTEXTURE_H
