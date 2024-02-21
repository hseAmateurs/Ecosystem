#ifndef ECOSYSTEM_CELL_H
#define ECOSYSTEM_CELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cmath>



class Cell
{
public:
    Cell(float radius, int size, float speed, const sf::Color& color, float posX, float posY);
    void setPosition(float x, float y);
    void setTargetPosition(float windowWidth, float windowHeight);
    void draw(sf::RenderWindow& window) {window.draw(shape);}
    //void setRadius(float radius) {shape.setRadius(radius);}
    template <typename patogen, typename body, typename macro, typename neutro>
    void update(std::vector<patogen>& patogens, std::vector<body>& bodys, std::vector<macro>& macros, std::vector<neutro>& neutros,sf::Time deltaTime);
    void setRandomVelocity(); // установка случайного вектора движения
    void customMove(sf::Vector2f velocity);
    float customGetRadius();
    void reflectionControl();
private:
    float speed;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f targetPosition;
    sf::Time interval;
    sf::Clock timer;
    sf::Time randomMoveInterval;

};

template <typename patogen, typename body, typename macro, typename neutro>
void Cell::update(std::vector<patogen>& patogens, std::vector<body>& bodys, std::vector<macro>& macros, std::vector<neutro>& neutros,sf::Time deltaTime){
    if (timer.getElapsedTime() > randomMoveInterval)
    {
        setRandomVelocity();
        float randomSeconds = static_cast<float>(std::rand() % 5 + 1); // Случайное число от 1 до 5
        randomMoveInterval = sf::seconds(randomSeconds);
        timer.restart();
    }
    reflectionControl();
    for (auto& otherCell : neutros){
        if (&otherCell != this){ // collision with itself
            sf::Vector2f otherPosition = otherCell.shape.getPosition();
            sf::Vector2f direction = otherPosition - shape.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if(shape.getGlobalBounds().intersects(otherCell.shape.getGlobalBounds())){
                velocity = shape.getPosition()-otherCell.shape.getPosition();
                otherCell.velocity = otherCell.shape.getPosition()-shape.getPosition();
            }
        }
    }
    for (auto& otherCell : patogens){
        if (&otherCell != this){ // collision with itself
            sf::Vector2f otherPosition = otherCell.shape.getPosition();
            sf::Vector2f direction = otherPosition - shape.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (shape.getGlobalBounds().intersects(otherCell.shape.getGlobalBounds())){
                velocity = shape.getPosition()-otherCell.shape.getPosition();
                otherCell.velocity = otherCell.shape.getPosition()-shape.getPosition();
            }
        }
    }
    for (auto& otherCell : bodys){
        if (&otherCell != this){ // collision with itself
            sf::Vector2f otherPosition = otherCell.shape.getPosition();
            sf::Vector2f direction = otherPosition - shape.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (shape.getGlobalBounds().intersects(otherCell.shape.getGlobalBounds())){
                velocity = shape.getPosition()-otherCell.shape.getPosition();
                otherCell.velocity = otherCell.shape.getPosition()-shape.getPosition();
            }
        }
    }
    for (auto& otherCell : macros){
        if (&otherCell != this){ // collision with itself
            sf::Vector2f otherPosition = otherCell.shape.getPosition();
            sf::Vector2f direction = otherPosition - shape.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (shape.getGlobalBounds().intersects(otherCell.shape.getGlobalBounds())){
                velocity = shape.getPosition()-otherCell.shape.getPosition();
                otherCell.velocity = otherCell.shape.getPosition()-shape.getPosition();
            }
        }
    }
    shape.move(velocity * deltaTime.asSeconds());
}

#endif //ECOSYSTEM_CELL_H
