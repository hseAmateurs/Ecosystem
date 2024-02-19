#ifndef ECOSYSTEM_GLOBALFUNC_H
#define ECOSYSTEM_GLOBALFUNC_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "patogenCell.h"
#include "BodyCell.h"
#include "MacroCell.h"
#include "NeutroCell.h"

//void createCells(std::vector<Cell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);
void createMacroCells(std::vector<MacroCell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);
void createPatogenCells(std::vector<PatogenCell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);
void createBodyCells(std::vector<BodyCell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);
void createNeutroCells(std::vector<NeutroCell>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color,sf::RenderWindow& window);

void csvInput(const std::string& fileName, std::vector<float>& radiusArr, std::vector<int>& sizeArr, std::vector<float>& speedArr, std::vector<int>& countArr);

#endif