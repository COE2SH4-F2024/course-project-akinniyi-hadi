#include "Player.h"
#include <iostream>



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    sfood = thisFood;
    playerPosList = new objPosArrayList();
    dir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX()/2,
                    thisGMRef->getBoardSizeY()/2,
                    '@');

    playerPosList->insertHead(headPos);
    
    // more actions to be included
    //playerPosList.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    //playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    //playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic

    switch(input)
    {
        case 'W':
        case 'w':
                        
            if (dir != DOWN)
            {
                dir = UP;
            }
            break;
                   
        case 'S':
        case 's':    
            if (dir != UP)
            {
                dir = DOWN;
            }
            break;
                        
        case 'A':
        case 'a':
            if (dir != RIGHT)
            {
                dir = LEFT;
            }
            break;
                        
        case 'D':
        case 'd':
            if (dir != LEFT)
            {
                dir = RIGHT;
            }
            break;
    }        
}

void Player::movePlayer()
{
    
    temp = playerPosList->getHeadElement();     //Intermiadiate element being assigned the current Head element position

    // PPA3 Finite State Machine logic
    switch(dir)
    {
        
        case UP:
        temp.pos->y--;
        if(temp.pos->y < 0)
        {
            temp.pos->y = mainGameMechsRef->getBoardSizeY()-1;
        }
        break;

        case DOWN:
        temp.pos->y++;
        if(temp.pos->y >= mainGameMechsRef->getBoardSizeY())
        {
            temp.pos->y = 0;
        }
        break;

        case LEFT:
        temp.pos->x--;
        if(temp.pos->x < 0)
        {
            temp.pos->x = mainGameMechsRef->getBoardSizeX()-1;
        }
        break;

        case RIGHT:
        temp.pos->x++;
        if(temp.pos->x >= mainGameMechsRef->getBoardSizeX())
        {
            temp.pos->x = 0;
        }
        break;

        case STOP:
        default:
        break;

        
    }

    if(checkFoodConsumption())                              //If The player collides with Food
    {
        if(SuperFood())                                     //If the food was a SuperFood
        {
            if(playerPosList->getSize()>4 && playerPosList->getSize()<=10)
            {
                playerPosList->removeTail();                // A player size of 4<size<=10, will cause the player to gain no increase in size
            }
            if(playerPosList->getSize()>10)
            {
                playerPosList->removeTail();
                playerPosList->removeTail();                // A player size of size>10, will cause the player to decrease in size by 1 unit
            }
            playerPosList->insertHead(temp);
            mainGameMechsRef->incrementScore();             //Eating a Super Food assures increase in score by 2 points rather than 1, regardless of size
            mainGameMechsRef->incrementScore();
        }else{
            increasePlayerLength();                         //If the Food was regular, then increase the length of the player
            mainGameMechsRef->incrementScore();             //And increase points by 1
            //playerPosList->insertHead(temp);              
        }
    }
    else{
        playerPosList->removeTail();                        //Under Normal circumstances, the snake moves
        playerPosList->insertHead(temp);
    }

    if(checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
    }
}

// More methods to be added

//Returns true if player collides with Food
bool Player::checkFoodConsumption()
{
    for(int i = 0; i<5; i++)
    {
        if(sfood->getFoodPos()->getElement(i).pos->x == playerPosList->getHeadElement().pos->x &&sfood->getFoodPos()->getElement(i).pos->y == playerPosList->getHeadElement().pos->y)
        {
            return true;
        }
    }
    return false;
}

//Returns true if Player collides with a supe food
bool Player::SuperFood()
{
    for(int i = 0; i<5; i++)
    {
        if(sfood->getFoodPos()->getElement(i).pos->x == playerPosList->getHeadElement().pos->x &&sfood->getFoodPos()->getElement(i).pos->y == playerPosList->getHeadElement().pos->y)
        {
            if(sfood->getFoodPos()->getElement(i).symbol == '$')
            {
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

void Player::increasePlayerLength()
{
    playerPosList->insertHead(temp);
}

//Returns true if the player collides with itself
bool Player::checkSelfCollision()
{
    if(playerPosList->getSize() <= 4)
    {
        return false;
    }
    for(int i = 1; i<playerPosList->getSize(); i++)
    {
        if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y)
        {
            return true;
        }
    }
    return false;
}