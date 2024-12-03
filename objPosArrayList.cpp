#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

        objPos* aList;
        int listSize;
        int arrayCapacity;


objPosArrayList::objPosArrayList()
{    
    arrayCapacity = ARRAY_MAX_CAP;                  //300 by Default
    listSize = 0;                                   //List is initially empty    
    
    aList = new objPos[ARRAY_MAX_CAP];              //Creates a 300 ObjPos array on heap
}

objPosArrayList::~objPosArrayList()                 //Deallocates heap members
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList &sList)
{
    listSize = sList.listSize;
    arrayCapacity = sList.arrayCapacity;
    aList = new objPos[ARRAY_MAX_CAP];

    for (int i=0; i<listSize; i++)
    {
        aList[i] = sList.aList[i];
    }
}

// Copy Assignment Operator 
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &sList)
{
    if(this != &sList)  
    {
        this->listSize = sList.listSize;
        this->arrayCapacity = sList.arrayCapacity;

           
        for(int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = sList.aList[i];
        }

    }
    return *this;
}


void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; // Shifting all elements towards the tail to create space at the head
    }
    
    aList[0] = thisPos; // Inserts an element at the head
    listSize++;
}
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }
    
    aList[listSize] = thisPos;  // Inserts an element at the tail
    listSize++;
}


void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        return;
    }

    for(int i=0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];  // Shifts all elements towards the front (the head)
    }
    listSize--;
}
void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        return;
    }

    listSize--;
}    

int objPosArrayList::getSize() const
{
    return listSize;
}


objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}
objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}