#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cell;

template <typename celltype> 
std::vector<celltype> createCells(std::vector<celltype>& cellVector,int count, int windowWidth,int windowHeight,float radius, int size, float speed,sf::Color color); // geeksforgeeks
