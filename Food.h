#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "objPosArrayList.h"



class Food
{
    private:
        objPosArrayList* foodPosList;
    
    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockOff);

        objPosArrayList* getFoodPos()const;
};

#endif