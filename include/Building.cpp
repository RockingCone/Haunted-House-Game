#pragma once
#include <iostream>
#include <cstdlib>
#include "Building.h"

using namespace std;


Building::Building()    // Default Constructor. Sets all variables to 0 or NULL
{
    groundFloor = NULL;
    currentFloor = NULL;
    totalChecks = 0;
    difficulty = 0;
}

Building::Building(int floors, int diff)    // Constructor. Sets variables according to inputs.
{
    groundFloor = NULL;
    currentFloor = NULL;
    totalChecks = 0;
    difficulty = 0;


    for(int i = 0; i < floors; i++)
    {
        addFloor();
    }

    currentFloor = groundFloor;
    
    switch(diff)
    {
        case 1:
            totalChecks = 5;
            difficulty = diff;
            break;
        case 2:
            totalChecks = 4;
            difficulty = diff;
            break;
        case 3:
            totalChecks = 3;
            difficulty = diff;
            break;
        case 4:
            totalChecks = 2;
            difficulty = diff;
            break;
        default:
            cout << "Not Valid Difficulty" << endl;
            break;
    }
}

Building::~Building()   // Destructor. Deletes all pointers in linked list.
{
    if (!groundFloor)
    {
        return;
    }
    if (groundFloor && !(groundFloor->nextFloor))
    {
        delete[] groundFloor;
        return;
    }
    do
    {
        if (groundFloor)
        {
            currentFloor = groundFloor;
            groundFloor = groundFloor->nextFloor;
            delete[] currentFloor;
        }
        if (!(groundFloor->nextFloor) && groundFloor)
        {
            delete[] groundFloor;
            return;
        }
    } while (groundFloor->nextFloor);
    if (groundFloor)
    {
        cout << "Err:Memory Leak\n";
    }
    return;
}


bool Building::checkDoor()
{
    /*
        Create logic to check a guess against the true door. If it fails, check if the player has tries left. 
        If they do, print a warning message and return to caller and return true. If they do not, print a fail message and return false.
        If the player guesses the correct door, call moveUp() and return true.
    */


    int guess = 0;
    int guesses;
    int doorNum = 1;
    guesses = totalChecks;

    while (guess != currentFloor->trueDoor){
        BeginDrawing();
        ClearBackground(GRAY);
        // Draw Doors
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 2; j++){
                doorNum = i + 1 + j*5;
                if (doorNum <= currentFloor->doors){
                    if (currentFloor->opened[doorNum - 1]){
                        DrawRectangle(120 + 360 * i, 40 + 520 * j, 120, 480, DARKBROWN);
                        DrawRectangle(240 + 360 * i, 40 + 520 * j, 120, 480, BLACK);
                    }
                    else {
                        DrawRectangle(120 + 360 * i, 40 + 520 * j, 240, 480, DARKBROWN);
                    }
                }
            }
        }
        EndDrawing();

        // Lose Condition
        if (guesses == 0){
            victory = 0;
            return false;
        }

        // Detect User input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 pos = GetMousePosition();
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 2; j++){
                    doorNum = i + 1 + j*5;
                    if (doorNum <= currentFloor->doors && !currentFloor->opened[doorNum]){
                        if (pos.x > (120 + 360 * i) && pos.x < (360 + 360 * i)){
                            if (pos.y > (40 + 520 * j) && pos.y < (520 + 520 * j)){
                                guess = doorNum;
                                guesses--;
                                currentFloor->opened[doorNum - 1] = 1;
                            }
                        }
                    }
                }
            }
        }

        // Close on user input
        if (WindowShouldClose()){
            victory = 0;
            return false;
        }
    }

    // Draw Level one last time then add delay to smooth transition
    BeginDrawing();
    ClearBackground(GRAY);
    // Draw Doors
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 2; j++){
            doorNum = i + 1 + j*5;
            if (doorNum <= currentFloor->doors){
                if (currentFloor->opened[doorNum - 1] && doorNum != currentFloor->trueDoor){
                    DrawRectangle(120 + 360 * i, 40 + 520 * j, 120, 480, DARKBROWN);
                    DrawRectangle(240 + 360 * i, 40 + 520 * j, 120, 480, BLACK);
                }
                else if (currentFloor->opened[doorNum - 1] && doorNum == currentFloor->trueDoor){
                    DrawRectangle(120 + 360 * i, 40 + 520 * j, 120, 480, DARKBROWN);
                    DrawRectangle(240 + 360 * i, 40 + 520 * j, 120, 480, WHITE);
                }
                else {
                    DrawRectangle(120 + 360 * i, 40 + 520 * j, 240, 480, DARKBROWN);
                }
            }
        }
    }
    EndDrawing();
    WaitTime(0.2);

    
    // Move to next floor 
    if (currentFloor->nextFloor){
        moveUp();
    }
    else {
        victory = 1;
        return false;
    }
    
    return true;
}

// void Building::printMessage(int messageType)
// {
//     /*
//         Prints messages for the game. The function can print one of 5 different types of messages. 
//         1. Wrong Guess Message (Multiple random messages)
//         2. Correct Guess/ Next Floor Message (Random messages)
//         3. Win Message (random messages)
//         4. Lose Message (random messages)
//     */
//     int msg = rand() % 5;
//     switch(messageType){
//         case(1):
//             // Randomly choose one of five different messages saying that the guess is incorrect.
//             switch(msg){
//                 case(0):
//                     cout << "Sorry, that's not right.\n";
//                     break;
//                 case(1):
//                     cout << "Wrong answer.\n";
//                     break;
//                 case(2):
//                     cout << "Incorrect.\n";
//                     break;
//                 case(3):
//                     cout << "Nope, wrong door.\n";
//                     break;
//                 case(4):
//                     cout << "Wrong door, too bad.\n";
//                     break;
//             }
//             break;
//         case(2):
//             // Randomly choose one of five differect messages saying that the guess is correct.
//             switch(msg){
//                 case(0):
//                     cout << "Correct.\n";
//                     break;
//                 case(1):
//                     cout << "Good job, that's correct.\n";
//                     break;
//                 case(2):
//                     cout << "Well done, you chose the right door.\n";
//                     break;
//                 case(3):
//                     cout << "Impressive, you've chosen the correct door.\n";
//                     break;
//                 case(4):
//                     cout << "That is correct.\n";
//                     break;
//             }
//             break;
//         case(3):
//             cout << "You win.";
//             break;
//         case(4):
//             cout << "You lose.";
//             break;
//     }
// }

// bool Building::gameLevel()
// {
//     // randomDoor(currentFloor);
//     while(checkDoor());
//     return false;
// }

/************************************************************************* Private Methods *******************************************************************************/

void Building::moveUp()
{
    /*
        Moves the player to the next floor. Called when the player guesses the correct door 
        on a given floor. Simply change the currentFloor variable to point to the next node in 
        the linked list.
    */
   currentFloor = currentFloor->nextFloor;
}

void Building::addFloor()
{
    /*
        Adds a floor to the linked list. This is a private method. It can only be called by the constructor.
        The correct door and number of doors are set here.
    */
    groundFloor = new Floor;
    groundFloor->nextFloor = currentFloor;
    groundFloor->doors = rand() % 5 + 6;
    groundFloor->trueDoor = rand() % groundFloor->doors + 1;
    for (int i = 0; i < 10; i++){
        groundFloor->opened[i] = 0;
    }
    currentFloor = groundFloor;
}

// void Building::randomDoor(Floor* current)
// {
//     /*
//         This generates the random door which is used on each floor. This is a private method. It can only be called by
//         moveUp()
//     */
// }