#ifndef ECOSYSTEM_GLOBALFUNC_H
#define ECOSYSTEM_GLOBALFUNC_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

void createCells(std::vector<Cell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);
void csvInput(const std::string& fileName, std::vector<float>& radiusArr, std::vector<int>& sizeArr, std::vector<float>& speedArr, std::vector<int>& countArr);

#endif