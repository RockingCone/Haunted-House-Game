#pragma once
#include <iostream>


using namespace std;


struct Floor
{
    Floor* nextFloor;
    int doors;
    int trueDoor;
    bool opened[10];
};

class Building
{
    private:
    Floor* groundFloor;         // The head of the linked list
    Floor* currentFloor;        // The current floor the player is on
    unsigned int totalChecks;   // The total number of checks a player has left for the doors on a given floor
    unsigned int difficulty;    // Sets the difficulty for the haunted building game

    public:
    bool victory;               // Bool that stores whether you won or not
    
    Building();

    Building(int floors, int diff);

    ~Building();

    bool checkDoor();

    // void printMessage(int messageType);

    // bool gameLevel();

    private:
    void addFloor();

    void moveUp();

    // void removeFloor();

    // void randomDoor(Floor* current);

};