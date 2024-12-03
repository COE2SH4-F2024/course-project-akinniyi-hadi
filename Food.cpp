#include "Food.h"

Food::Food()
{
    foodPosList = new objPosArrayList();
}        
Food::~Food()
{
    delete foodPosList;
}

void Food::generateFood(objPosArrayList* blockOff)              //Generates Food at random Locations
{
    int flag,xsize,ysize,xt,yt;
    int posi[10][20] = {{0}};                                   //A 2D Array with coordinates which matches the maps.
    objPos temp;

    flag = 1;
    srand(time(NULL));
    xsize = 20;
    ysize = 10;

    for(int i = 0; i<10; i++)                                   //Prevents food from Spawning on the same column as the Head element
    {
        posi[i][blockOff->getHeadElement().pos->x] = 1;
    }

    for(int i = 0;i<20;i++)                                     //Prevents food from Spawning on the same row as the Head element
    {
        posi[blockOff->getHeadElement().pos->y][i] = 1;
    }

    for(int i = 1; i<blockOff->getSize(); i++)                  //Prevents food from Spawning in the position of any element
    {
        posi[blockOff->getElement(i).pos->y][blockOff->getElement(i).pos->x] = 1;
    }

    for(int i = 0; i<5;i++)
    {
        while(flag)                                             //Loop that keeps iterating until a position that hasn't been occupied is generated
        {
            flag = 0;
            xt = rand()%xsize;
            yt = rand()%ysize;
            if(posi[yt][xt] == 1)
            {
                flag = 1;
            }
        }

        if(i<4)                                                 //First 4 foods are regular and the last one are Super
        {
            temp = objPos(xt, yt, '*');
        }else{
            temp = objPos(xt, yt, '$');
        }


        if(foodPosList->getSize()>= 5)                          //Prevents the Food list memory from filling up
        {
            foodPosList->removeTail();
        }
        foodPosList->insertHead(temp);
        posi[yt][xt] = 1;       
        
        flag = 1;
    }
}

objPosArrayList* Food::getFoodPos()const
{
    return foodPosList;
}