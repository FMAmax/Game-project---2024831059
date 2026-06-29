#include "raylib.h"
#include<bits/stdc++.h>
#include<iostream>
#include<raymath.h>
using namespace std;

Color white_tan={232,205,181,255};
Color orange={201,100,66,255};
Color green={106,125,91,255};
Color dark_green={43,51,54,255};
Color blue={21,115,178,255};

const int CELL_SIZE=30;
const int GRID_WIDTH=30;
const int GRID_HEIGHT=30;

double last_update_time=0;

bool event_trigger(double interval){
    double current_time=GetTime();
    if(current_time-last_update_time>=interval){
        last_update_time=current_time;
        return true;
    }
    return false;
}

class Food{
    public :
    Vector2 position = random_pos();

    void draw(){
        DrawCircle(position.x * CELL_SIZE, position.y *CELL_SIZE, CELL_SIZE/2, green);
    }
    Vector2 random_pos(){
        float x=GetRandomValue(0,GRID_WIDTH-1);
        float y=GetRandomValue(0,GRID_HEIGHT-1);
        return Vector2{x,y};
    }

};

class Snake{

    public:
    deque<Vector2> body={Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction={1,0};

    void draw(){
       
        for(unsigned int i = 0;i<body.size();i++){
            float x = body[i].x;

            float y = body[i].y;
            Rectangle segment = Rectangle{x*CELL_SIZE,y*CELL_SIZE,(float)CELL_SIZE,(float)CELL_SIZE};
            DrawRectangleRounded(segment, 0.5,6,orange);
        }
        
    }
    void update(){
        body.pop_back();
        body.push_front(Vector2Add(body[0],direction));
    }
};

int main()
{
    const int screen_Width  = CELL_SIZE * GRID_WIDTH;
    const int screen_Height = CELL_SIZE * GRID_HEIGHT;
    
    
    InitWindow(screen_Width, screen_Height, "Snakity Snake");
    
    SetTargetFPS(60);
    Food food=Food();
    Snake snake=Snake();
    
    while (WindowShouldClose() == false)
    {   
        if(event_trigger(0.2)){
            snake.update();
        }
        BeginDrawing();
        ClearBackground(white_tan);
        food.draw();
        snake.draw();
        EndDrawing();
    }



    CloseWindow();
    return 0;
}



