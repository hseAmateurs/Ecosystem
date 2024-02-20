#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

typedef struct AnimationParameters{
    // static functions
    float(*getOffset)(float angle, AnimationParameters* parameters);
    void(*updatePulsationAspect)(AnimationParameters* parameters);

    // const
    int   wavePeriod;
    float rotationSpeed;
    float pulsationSpeed;
    float pulsationSpan;
    float pulsationWaveHeight;

    // dynamic variables
    float delta;
    float currentPulsationAspect;




}AnimationParameters;




class Cell : public sf::Drawable, public sf::Transformable {

public:

    explicit Cell(sf::Vector2f center = {0,0}, float radius = 100, int pointCount = 180, sf::Color color = sf::Color::White);
    void update(sf::Time elapsed);

protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float radius;
    sf::Vector2f center;
    sf::VertexArray m_vertices;

    int pointsCount;
    sf::Color color;
    AnimationParameters Animation;

};







#endif //ECOSYSTEM_CELL_H
