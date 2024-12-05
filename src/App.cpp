#include "App.hpp"
#include <raylib.h>
#include "GamePage.hpp"

namespace samaya{

    App::App(int width, int height, const char* title)
        : game(width, height)
    {
        InitWindow(width, height, title);
        SetTargetFPS(60);
    }

    App::~App(){
        CloseWindow();
    }

    App& App::run(){
        while(!WindowShouldClose()){
            processInput();
            update();
            paint();
        }
        return *this;
    }


    void App::processInput(){
        game.processInput();
    }
    void App::update(){
        game.update(GetFrameTime());
    }
    
    void App::paint()
    {
        BeginDrawing();
        ClearBackground(WHITE);
        game.paint();
        EndDrawing();
    }


}