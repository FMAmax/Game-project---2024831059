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
const int offset = 75;

double last_update_time=0;

bool element_indeque(Vector2 element, const deque<Vector2>& deque ){
    for(unsigned int i=0;i<deque.size();i++){
        if(Vector2Equals(deque[i],element))
        return true;
    }
    return false;
}

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
    Vector2 position;

    Food(deque<Vector2> snakebody){
        position = random_pos(snakebody);
    }

    void draw(){
        DrawCircle(offset + position.x * CELL_SIZE + CELL_SIZE / 2,offset + position.y * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE / 2, green);
    }
    Vector2 random_cell(){
        float x=GetRandomValue(0,GRID_WIDTH-2);
        float y=GetRandomValue(0,GRID_HEIGHT-2);
        return Vector2{x,y};
    }
    Vector2 random_pos(deque<Vector2> snakebody){
       
        Vector2 position = random_cell();
        while(element_indeque(position, snakebody)){
            position = random_cell();
        }
        return position;  
        
    }

};

class Snake{

    public:
    deque<Vector2> body={Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction={1,0};
    bool add_segment = false;

    void draw(){
       
        for(unsigned int i = 0;i<body.size();i++){
            float x = body[i].x;

            float y = body[i].y;
            Rectangle segment = Rectangle{offset + x*CELL_SIZE,offset + y*CELL_SIZE,(float)CELL_SIZE,(float)CELL_SIZE};
            DrawRectangleRounded(segment, 0.5,6,orange);
        }
        
    }
    void update(){
        body.push_front(Vector2Add(body[0],direction));
        if(add_segment){
            add_segment = false;
        }
        else{
            body.pop_back();
        }
    }
    void reset(){
        body={Vector2{6,9},Vector2{5,9},Vector2{4,9}}; 
        direction = {1,0};
    }

};

class Game{
    public :
    Snake snake = Snake();
    Food food = Food(snake.body);
    int score = 0;
    bool running = true;
    void draw(){
        snake.draw();
        food.draw();
    }
    void update(){ 
        if(running){
        snake.update();
        check_collision_with_food();
        check_collision_edges();
        check_collision_head();
        }

    }
    void check_collision_with_food(){
        if(Vector2Equals(snake.body[0],food.position)){
            cout<< "food eaten"<<" ";
            food.position = food.random_pos(snake.body);
            snake.add_segment = true;
            score++;
        }
    }
    void check_collision_edges(){
        if(snake.body[0].x == GRID_WIDTH || snake.body[0].x == -1 ){
            game_over();
        }
        if(snake.body[0].y == GRID_HEIGHT || snake.body[0].y == -1 ){
            game_over();
        }   
    }
    void game_over(){
        snake.reset();
        food.position = food.random_pos(snake.body);
        running = false;
        score = 0;
    }
    void check_collision_head(){
        deque<Vector2> headless_body = snake.body;
        headless_body.pop_front();
        if(element_indeque(snake.body[0],headless_body)){
            game_over();
        }

    }
};

int main()
{
    const int screen_Width  = CELL_SIZE * GRID_WIDTH;
    const int screen_Height = CELL_SIZE * GRID_HEIGHT;
    
    
    InitWindow(2*offset + screen_Width,2*offset + screen_Height, "Snakity Snake");
    
    SetTargetFPS(60);
    
    Game game= Game();
    
    while (WindowShouldClose() == false)
    {   
        if(event_trigger(0.175)){
            game.update();
        }
        if(IsKeyPressed(KEY_UP) and game.snake.direction.y != 1){
            game.snake.direction= {0,-1};
            game.running = true;
        }
        if(IsKeyPressed(KEY_DOWN) and game.snake.direction.y != -1){
            game.snake.direction= {0,1};
            game.running = true;
        }
        if(IsKeyPressed(KEY_RIGHT) and game.snake.direction.x != -1){
            game.snake.direction= {1,0};
            game.running = true;
        }
        if(IsKeyPressed(KEY_LEFT) and game.snake.direction.x != 1){
            game.snake.direction= {-1,0};
            game.running = true;
        }

        BeginDrawing();

        ClearBackground(white_tan);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)CELL_SIZE * GRID_HEIGHT + 10, (float)CELL_SIZE * GRID_WIDTH + 10}, 5, dark_green);
         DrawText("Snakity Snake", offset - 5, 20, 40, dark_green);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + CELL_SIZE * GRID_HEIGHT + 10, 40, dark_green);
        game.draw();

        EndDrawing();
    }



    CloseWindow();
    return 0;
}
