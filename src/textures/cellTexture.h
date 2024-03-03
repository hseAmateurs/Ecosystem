#ifndef ECOSYSTEM_CELLTEXTURE_H
#define ECOSYSTEM_CELLTEXTURE_H

#include <SFML/Graphics.hpp>

namespace texture {

    struct AnimationParameters {
        // static functions
        float (*getOffset)(float angle, AnimationParameters *parameters);

        void (*updatePulsationAspect)(AnimationParameters *parameters);

        // const
        int wavePeriod;
        float rotationSpeed;
        float pulsationSpeed;
        float pulsationSpan;
        float pulsationWaveHeight;

        // dynamic variables
        float delta;
        float currentPulsationAspect;
    };


    class CellTexture : public sf::Drawable, public sf::Transformable {

    public:

        explicit CellTexture(AnimationParameters texture, sf::Vector2f center = {0, 0}, float radius = 15,
                             int pointsCount = 180,
                             sf::Color color = sf::Color::Magenta)
                :
                center(center), radius(radius), m_vertices(sf::TriangleFan, pointsCount + 2),
                pointsCount(pointsCount),
                color(color), parameters(texture) { setRotationDirection(rand() % 2); };

        void update();

        void changeCenter(sf::Vector2f newCenter);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Vector2f getRadiusVector(const float &angle, const float &radius) const;

        void setRotationDirection(bool isRight);

        AnimationParameters parameters;

        int rotationDirection;

        float radius;
        sf::Vector2f center;
        sf::VertexArray m_vertices;

        int pointsCount;
        sf::Color color;
    };
}

#endif //ECOSYSTEM_CELLTEXTURE_H
