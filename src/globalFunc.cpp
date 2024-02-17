#include "cell.h"
#include "globalFunc.h"
#include <cstdlib>


void createCells(std::vector<Cell>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color,sf::RenderWindow& window){
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*static_cast<int>(radius));
        float posY=rand()%(windowHeight-2*static_cast<int>(radius)); // this will be a problem later on. i don't care.
        Cell cell(radius,size,speed,color,posX,posY);
        cellVector.push_back(cell);
    }
    for(int i=0;i<count;++i){
        cellVector.at(i).draw(window);
    }
}