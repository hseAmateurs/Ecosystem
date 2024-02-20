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
    template<typename T>
    void update(std::vector<T>& cells, sf::Time deltaTime);
    void setRandomVelocity(); // установка случайного вектора движения
private:
    float speed;
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f targetPosition;
    sf::Time interval;
    sf::Clock timer;
    sf::Time randomMoveInterval;

};

template<typename T>
void Cell::update(std::vector<T>& cells, sf::Time deltaTime)
{
    sf::Vector2f currentPosition = shape.getPosition();
    sf::Vector2f direction = targetPosition - currentPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 1.0f){
        direction /= distance;
        velocity = direction * speed * deltaTime.asSeconds();
    }
    // Проверка на коллизии с другими клетками
    for (auto& otherCell : cells)
    {
        if (&otherCell != this) // Не обрабатываем коллизии с самим собой
        {
            sf::Vector2f otherPosition = otherCell.shape.getPosition();
            sf::Vector2f direction = otherPosition - currentPosition;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Если есть пересечение с другой клеткой
            if (distance < shape.getRadius() + otherCell.shape.getRadius())
            {
                // Обработка коллизии
                sf::Vector2f thisVelocity = velocity;
                sf::Vector2f otherVelocity = otherCell.velocity;

                sf::Vector2f normal = direction / distance;

                float thisDot = thisVelocity.x * normal.x + thisVelocity.y * normal.y;
                float otherDot = otherVelocity.x * normal.x + otherVelocity.y * normal.y;

                float optimizedP = (2.0 * (thisDot - otherDot)) / (shape.getRadius() + otherCell.shape.getRadius());

                velocity.x -= optimizedP * otherCell.shape.getRadius() * normal.x;
                velocity.y -= optimizedP * otherCell.shape.getRadius() * normal.y;

                otherCell.velocity.x += optimizedP * shape.getRadius() * normal.x;
                otherCell.velocity.y += optimizedP * shape.getRadius() * normal.y;

                // Перемещение клеток
                this->targetPosition = sf::Vector2f(currentPosition.x+velocity.x,currentPosition.y+velocity.y);
                //otherCell.targetPosition = sf::Vector2f(otherCell.().x+otherCell.velocity.x,otherCell.getPosition().y+otherCell.velocity.y);
                shape.move(velocity * deltaTime.asSeconds());
                otherCell.shape.move(otherCell.velocity * deltaTime.asSeconds());
            }
        }
    }
    shape.move(velocity);
    // Обновление таймера для смены целевой позиции
    if (timer.getElapsedTime() >= interval)
    {
        setTargetPosition(1600, 900);
        timer.restart();
    }
}




#endif //ECOSYSTEM_CELL_H
