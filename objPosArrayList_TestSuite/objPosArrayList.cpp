#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

        objPos* aList;
        int listSize;
        int arrayCapacity;


objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

objPosArrayList::objPosArrayList(const objPosArrayList &sList)
{
    // We want Deep Copy: All data elements in the source list are copied not just its address
    // What does SHALLOW COPY look like:
    /*
    sizeList = sList.sizeList;
    sizeArray = sList.sizeArray;
    aList = sList.aList;    // Problem: Only the address of the source list is copied in our list's aList pointer
                            // Thus, my new ArrayList points to the same heap array as sList
                            // Not good, didn't really copy
    */

    // DEEP COPY:
    listSize = sList.listSize;
    arrayCapacity = sList.arrayCapacity;
    aList = new objPos[ARRAY_MAX_CAP];

    for (int i=0; i<listSize; i++)
    {
        aList[i] = sList.aList[i];
    }
}

// Copy Assignment Operator (R6M4 3/4)
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &sList)
{
    if(this != &sList)  // Avoid self assignment
    {
        this->listSize = sList.listSize;
        this->arrayCapacity = sList.arrayCapacity;

        // Do deep copy    
        for(int i = 0; i < this->listSize; i++)
        {
            this->aList[i] = sList.aList[i];
        }

    }
    return *this;
    // this-> ensures that no implicit copied instance is created, which leads to memory inefficiency
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
    
    aList[0] = thisPos; // Inserting the element at the head, index: 0
    listSize++;
}
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }
    
    aList[listSize] = thisPos;  // Inserting the element at the tail, index: sizeList
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
        aList[i] = aList[i+1];  // Shifting towards the head, element i replaced by element i+1
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
    //if(index<0 || index >listSize)
    //{
    //    
    //}

    return aList[index];
}