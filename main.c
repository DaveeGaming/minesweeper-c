#include "raylib.h"
#include "game.h"
#include "global.h"

int main(void)
{


    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib mine sweeper");
    SetTargetFPS(60);  

    // LOAD TEXTURES AND VARIABLES AFTER SCREEN CREATION
    init();

    while (!WindowShouldClose())    
    {
        update();
        draw();
    }

    CloseWindow();       
    return 0;
}
