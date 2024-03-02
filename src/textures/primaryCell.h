#ifndef ECOSYSTEM_PRIMARYCELL_H
#define ECOSYSTEM_PRIMARYCELL_H

#include <SFML/Graphics.hpp>

namespace texture {

    struct AnimationParameters {
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


    class PrimaryCell : public sf::Drawable, public sf::Transformable {

    public:

        explicit PrimaryCell(sf::Vector2f center = {0, 0}, float radius = 15, int pointCount = 180,
                      sf::Color color = sf::Color::Magenta);

        void update();

        void changeCenter(sf::Vector2f newCenter);

    protected:

        virtual float getOffset(const float &angle) const;

        virtual void updatePulsationAspect();

        AnimationParameters parameters{};

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Vector2f getRadiusVector(const float &angle, const float &radius) const;

        float radius;
        sf::Vector2f center;
        sf::VertexArray m_vertices;

        int pointsCount;
        sf::Color color;


    };
}

#endif //ECOSYSTEM_PRIMARYCELL_H
