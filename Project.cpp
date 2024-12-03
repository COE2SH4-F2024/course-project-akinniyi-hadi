#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MacUILib.h"
#include "objPos.h"

#include "player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
int i,j,k; //Counters

//Universal Important Pointer
Player *myPlayer;
GameMechs* mygm;
Food* myFood;

objPos* Obj_array;
objPosArrayList* snakeFood;


objPos def;             //A reset position for intermediate ObjPos variables
objPos playerPos;






void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    
    exitFlag = false;
    mygm = new GameMechs();
    myFood = new Food();
    myPlayer = new Player(mygm, myFood);

    // The reset variables positions should be out of the map
    def.pos->x = 31;
    def.pos->y = 21;

    playerPos = myPlayer->getPlayerPos()->getHeadElement();     //Player position is the position of the head of the snake
    myFood->generateFood(myPlayer->getPlayerPos());
    snakeFood = myFood->getFoodPos();
   
}

void GetInput(void)
{
   mygm->collectAsyncInput();
}

void RunLogic(void)
{
    //Updating the Player's and Foods' positions
    playerPos = myPlayer->getPlayerPos()->getHeadElement();
    snakeFood = myFood->getFoodPos();

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //If the Player collides with any of the foods, food is generated at random points on the map
    for(i = 0; i<5; i++)
    {
        if(playerPos.pos->x == snakeFood->getElement(i).pos->x && playerPos.pos->y == snakeFood->getElement(i).pos->y)
        {
            myFood->generateFood(myPlayer->getPlayerPos());
        }
    }
}

void DrawScreen(void)
{
    
    MacUILib_clearScreen();

    objPos target = def;          //Intermediate ObjPos Variable for storing the position of a player
    objPos foodtarget = def;      //Intermediate ObjPos Variable for storing the position of a food

    //Updateing the Foods' and Player's positions
    snakeFood = myFood->getFoodPos();
    playerPos = myPlayer->getPlayerPos()->getHeadElement();


    MacUILib_printf("######################\n");

    for(i = 0; i<mygm->getBoardSizeY(); i++)                //y-axis
    {
        
        MacUILib_printf("#");


        for(j = 0; j<mygm->getBoardSizeX(); j++)            //x-axis
        {
            //Searches the Player list for any element that exist in the position (j,i)
            for(k =0; k<myPlayer->getPlayerPos()->getSize(); k++)
            {
                if(myPlayer->getPlayerPos()->getElement(k).pos->x == j && myPlayer->getPlayerPos()->getElement(k).pos->y == i)
                {
                    target = myPlayer->getPlayerPos()->getElement(k);       //Stores the position and symbol of the player in position (j,i)
                    break;
                }
            }
            //if(myPlayer->getPlayerPos()->getElement(k).pos->x == j && myPlayer->getPlayerPos()->getElement(k).pos->y == i)
            if(i == target.pos->y && j == target.pos->x)
            {
                MacUILib_printf("%c", myPlayer->getPlayerPos()->getElement(k).symbol);                       //Prints the Player symbol on its position on the screen
                target = def;                                               //Resets the information on target.
            }
            else{
                //Searches the Food list for any element that exist in the position (j,i
                for(k =0; k<5; k++)
                {
                    if(snakeFood->getElement(k).pos->x == j && snakeFood->getElement(k).pos->y == i)
                    {
                        foodtarget = snakeFood->getElement(k);              //Stores the position and symbol of the food in position (j,i)
                    }
                }
            
                if(i == foodtarget.pos->y && j == foodtarget.pos->x)
                {
                    MacUILib_printf("%c", foodtarget.symbol);               //Prints the Food's symbol on its position on the screen
                    foodtarget = def;                                           //Resets the information on target.
                }
                else{
                    MacUILib_printf(" ");
                }
            }
        }
        
        MacUILib_printf("#\n");
    }
    MacUILib_printf("######################\n\n");


    MacUILib_printf("Snake Head : (%d,%d,%c)\n", playerPos.pos->x,playerPos.pos->y,playerPos.symbol);
    
    //Displays the Foods' information
    MacUILib_printf("\n Food on the Table");                
    for(i = 0; i<myFood->getFoodPos()->getSize();i++)
    {
        MacUILib_printf("\n Food %d at (%d,%d,%c)",(i+1),myFood->getFoodPos()->getElement(i).pos->x, myFood->getFoodPos()->getElement(i).pos->y,myFood->getFoodPos()->getElement(i).symbol);
    }
    
    //Displays the Score and Snake Size
    MacUILib_printf("\n");
    MacUILib_printf("\n\nSCORE: %d \n", mygm->getScore());
    if(myPlayer->getPlayerPos()->getSize()>10)
    {
        MacUILib_printf("\n!!!!DANGER!!!!\n");
    }
    MacUILib_printf("\nSIZE: %d \n", myPlayer->getPlayerPos()->getSize());
    
    
    if(mygm->getLoseFlagStatus()== true)                        //Displays Meesage if one loses
    {
        mygm->setExitTrue();
    }

    exitFlag = mygm->getExitFlagStatus();
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(mygm->getLoseFlagStatus()== true)                        //Displays Meesage if one loses
    {
        MacUILib_printf("\n\nOh Well, You tried.\n");
        MacUILib_printf("At least, you didn't give up\n");
    }else{
        MacUILib_printf("You give up too easy mate.\n");
    }
    

    delete mygm;
    delete myFood;
    delete myPlayer;
    

    MacUILib_uninit();
}
