/* 
Написать спавн клеток в отдельных функциях. Есть setPosition, где передается x,y и draw, куда передается window sf::RenderWindow window
и векторы должны передаваться как ссылки. 
*/
#include "cell.h"
#include "globalFunc.h"
#include <cstdlib>

template <typename celltype> 
std::vector<celltype> createCells(std::vector<celltype>& cellVector,int count,int windowWidth,int windowHeight,float radius,int size,float speed,sf::Color color){
    for(int i=0;i<count;++i){
        float posX=rand()%(windowWidth-2*radius);
        float posY=rand()%(windowHeight-2*radius); // this will be a problem later on. i don't care.
        celltype cell(radius,size,speed,color,posX,posY);
        cellVector.push_back(cell);
    }
    return cellVector;
}

