#include "raylib.h"
#include<iostream>
using namespace std;

Color white_tan={232,205,181,255};
Color orange={201,100,66,255};
Color green={173,204,96,255};
Color dark_green={43,51,54,255};
Color blue={21,115,178,255};

const int CELL_SIZE=30;
const int GRID_WIDTH=30;
const int GRID_HEIGHT=30;

int main()
{
    const int screenWidth  = CELL_SIZE * GRID_WIDTH;
    const int screenHeight = CELL_SIZE * GRID_HEIGHT;


    InitWindow(screenWidth, screenHeight, "Snakity Snake");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
    
        BeginDrawing();
        ClearBackground(white_tan);
        // DrawText("Snake - press ESC to quit", 10, 10, 20, RAYWHITE);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}


