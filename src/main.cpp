/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "Building.cpp"

// Include Some Standard Libraries
#include <iostream>		// For Testing
#include <iomanip>
#include <string>		// For getline(&stream, string)
#include <time.h>		// For time(int)
#include <cstdlib>

using namespace std;

int main ()
{
	//Program Variables, Comment each one to describe its use
    int n = 0;								// Number of Floors
    int d = 0;								// Difficulty of Game
	bool active = 1;						// Bool for whether or not the game is active
	int nX[5] = {95, 460, 825, 1190, 1550};	// X-Positions of the floor number buttons
	int nY[2] = {350, 715};					// Y-Positions of the floor number buttons
	int dX[4] = {168, 606, 1044, 1482};		// X-Positions of the difficulty buttons
	int dY = 438;							// Y-Positions of the difficulty buttons
	int screenW = 1920;						// Width of screen
	int screenH = 1080; 					// Height of screen

    srand(time(0)); //Seed for random number generator. Uses the current time to ensure dynamic operation.
	
	InitWindow(screenW, screenH, "Haunted House");
	SetTargetFPS(60);
	ToggleFullscreen();

	while (active)	//Program Loop. This loop is infinite. You need to break from this loop with conditional statements and user input.
	{
		n = 0;
		d = 0;
		string str = "";
		int length1 = 0;
		int length2 = 0;
		
		// Wait for user input to start game
		length1 = MeasureText("Welcome to the Haunted House", 100);
		length2 = MeasureText("[Press Enter to Proceed]", 80);
        while(!IsKeyDown(KEY_ENTER) && active){
			BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Welcome to the Haunted House", (screenW - length1) / 2, 455, 100, MAROON);
            DrawText("[Press Enter to Proceed]", (screenW - length2) / 2, 545, 80, MAROON);
			EndDrawing();
			if (WindowShouldClose()){
				active = 0;
			}
        }
		str = "";
		length1 = 0;
		length2 = 0;

		// Make user choose a number of floors
		while ((n < 1 || n > 10) && active){
			BeginDrawing();
			ClearBackground(BLACK);
			// Render Prompt (How many floors would you like to climb?)
			DrawText("How many floors would\n    you like to climb?", 100, 0, 150, MAROON);
			// Render Buttons with the numbers
			for (int i = 0; i < 5; i++){
				string temp = "";
				for (int j = 0; j < 2; j++){
					DrawRectangle(nX[i], nY[j], 270, 270, GRAY);
					if (!(i == 4 && j == 1)){
						temp = char(i + 1 + j * 5 + 48);
						DrawText(temp.c_str(), nX[i] + 70, nY[j] + 20, 250, BLACK);
					}
					else {
						DrawText("10", nX[i] + 35, nY[j] + 20, 250, BLACK);
					}
				}
			}
			EndDrawing();
			if (WindowShouldClose()){
				active = 0;
			}

			// Select Number if button is pressed
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
				for (int i = 0; i < 5; i++){
					for (int j = 0; j < 2; j++){
						if (GetMousePosition().x > nX[i] && GetMousePosition().x < nX[i] + 270){
							if (GetMousePosition().y > nY[j] && GetMousePosition().y < nY[j] + 270){
								n = i + 1 + j * 5;
							}
						}
					}
				}
			}
		}
		str = "";
		length1 = 0;
		length2 = 0;

		// Make user choose difficulty
		while ((d < 1 || d > 4) && active){
			string temp = "";
			BeginDrawing();
			ClearBackground(BLACK);
			// Render Prompt (Choose you difficulty)
			DrawText("Choose your difficulty", 100, 0, 150, MAROON);
			// Render Buttons with the numbers
			for (int i = 0; i < 4; i++){
				temp = char(i + 49);
				Rectangle rect = {dX[i], dY, 270, 270};
				DrawRectangleRec(rect, GRAY);
				// DrawRectangleRoundedLinesEx(rect, 0.1f, 10, 4, WHITE);
				DrawText(temp.c_str(), dX[i] + 70, dY + 20, 250, BLACK);
			}
			EndDrawing();
			if (WindowShouldClose()){
				active = 0;
			}

			// Select Number if button is pressed
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
				for (int i = 0; i < 4; i++){
					if (GetMousePosition().y > dY && GetMousePosition().y < dY + 270){
						if (GetMousePosition().x > dX[i] && GetMousePosition().x < dX[i] + 270){
							d = i + 1;
						}
					}
				}
			}
		}
		str = "";
		length1 = 0;
		length2 = 0;

		if (active){
			// Declare Building Variable based off of user input
			Building hh_b(n, d);
			// Main Game Loop
			while(hh_b.checkDoor() && active);
			if (hh_b.victory){
				length1 = MeasureText("You Won!", 200);
				length2 = MeasureText("[Press Enter to Proceed]", 80);
				while (!IsKeyDown(KEY_ENTER) && active){
					BeginDrawing();
					ClearBackground(BLACK);
					DrawText("You Won!", (screenW - length1) / 2, 400, 200, MAROON);
					DrawText("[Press Enter to Proceed]", (screenW - length2) / 2, 600, 80, MAROON);
					EndDrawing();

					if (WindowShouldClose()){
						active = 0;
					}
				}
			}
			else if (!hh_b.victory){
				length1 = MeasureText("You Lost.", 200);
				length2 = MeasureText("[Press Enter to Proceed]", 80);
				while (!IsKeyDown(KEY_ENTER) && active){
					BeginDrawing();
					ClearBackground(BLACK);
					DrawText("You Lost.", (screenW - length1) / 2, 400, 200, MAROON);
					DrawText("[Press Enter to Proceed]", (screenW - length2) / 2, 600, 80, MAROON);
					EndDrawing();

					if (WindowShouldClose()){
						active = 0;
					}
				}
			}
		}

	}
}