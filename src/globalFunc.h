#ifndef ECOSYSTEM_GLOBALFUNC_H
#define ECOSYSTEM_GLOBALFUNC_H

#include <SFML/Graphics.hpp>
#include <vector>

void createCells(std::vector<Cell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);

#endif