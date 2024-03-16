#ifndef ECOSYSTEM_CELLTEXTURE_H
#define ECOSYSTEM_CELLTEXTURE_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace texture {

    struct ChangingRadius {

        ChangingRadius(float changingSpeed) : radiusChangingSpeed(changingSpeed) { };

        float getChangingRadiusOffset(sf::Time time) const {
            float x = time.asSeconds() * radiusChangingSpeed;
            return 1.f + x * powf(2,-x+2) * radiusChangingSpan;
        }

        bool isEndOfChagingRadius(sf::Time time) const {
            float x = time.asSeconds() * radiusChangingSpeed;
            return x>=2;
        }

        float radiusChangingSpeed;
        float radiusChangingSpan;
        float newRadius;
        float oldRadius;
    };

    struct Pulsation {

        float getPulsationOffset(sf::Time time) {
            float x = time.asSeconds() * pulsationSpeed;
            return 1.f + ( powf(sinf(x), 2) + powf(sinf(2*x), 1) ) * pulsationSpan;
        }

        bool isEndOfPulsation(sf::Time time) {
            float x = time.asSeconds() * pulsationSpeed;
            return (x >= M_PI);
        }

        float pulsationSpan;
        float pulsationSpeed;
    };

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
        Pulsation pulsation;
        ChangingRadius changingRadius;


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
                center(center), radius(radius), rotationDirection(rand() % 2 ? -1 : 1),
                m_vertices(sf::TriangleFan, pointsCount + 2), pointsCount(pointsCount + 2), color(color),
                parameters(animation), flag(false),
                isDying(false), isBirthing(false), isChangingRadius(false), isPulsation(false), innerTimer(sf::Time::Zero) {
            startBirthing();
        };

        void update(sf::Time elapsed);

        void changeCenter(sf::Vector2f newCenter) { center = newCenter; };

        void startDying();

        void startBirthing();

        void startPulsation();

        void changeRadius(float newRadius);

        bool isDead() const { return pointsCount==0; }

        bool isAnimDying() const { return isDying; }

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void updateDying();

        void updateChangingRadius();

        sf::Vector2f getRadiusVector(const float &angle, const float &radius) const;

        AnimationParameters parameters;

        int rotationDirection;

        float radius;
        sf::Vector2f center;
        sf::VertexArray m_vertices;

        int pointsCount;
        sf::Color color;


        bool isDying;
        bool isBirthing;
        bool isChangingRadius;
        bool isPulsation;

        sf::Time innerTimer;

        bool flag;
    };
}

#endif //ECOSYSTEM_CELLTEXTURE_H
