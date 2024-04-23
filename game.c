#include "raylib.h"
#include "raymath.h"
#include "game.h"
#include "global.h"
#include <stdlib.h>

#undef min
#undef max

#define N 15
#define M 15

typedef struct {
    bool hidden; int value;
} Tile;

const int designWidth = SCREEN_WIDTH;
const int designHeight = SCREEN_HEIGHT;
int currentW;
int currentH;
float scale;
RenderTexture2D canvas; 
Tile map[N][M];

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

Tile newTile(int value) {
    Tile t;
    t.value = value;
    t.hidden = false;
    return t;
}

void increment_neighbour(int x, int y) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if( x + i >= 0 && x + i < N &&
                y + j >= 0 && y + j < N &&
                map[x + i][y + j].value != -1
            )  map[x + i][y + j].value += 1;
        }
    }
}

void generateGameGrid() {
    // PLACE RANDOM BOMBS
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int random = rand() % 10; // 0-9
            if (!random) {
                map[i][j].value = -1;
                increment_neighbour(i, j);
            }
        }
    }
    //EASIEST IS IF YOU INCREMENT THE NEIGHBOURS WHEN U PLACE A BOMB
    //so we dont have to loop through it twice
}

void updateCursorControl() {
    int x = GetMouseX();
    int y = GetMouseY();

    // get mouse pos in scaled texture
    x /= scale;
    y /= scale;

    // Get which matrix element the player is clicking on
    x /= 16;
    y /= 16;

    map[x][y].hidden = false;
}


void drawGameGrid() {
        const int tile_start = 49;
        const int number_tile_start = 66;
        const int tile_size = 16;

        const Vector2 bomb_start = (Vector2){85,49};

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (map[i][j].hidden) {
                    DrawTextureRec(SPRITE_SHEET, (Rectangle){0,tile_start, tile_size, tile_size} , (Vector2){tile_size * i, tile_size * j}, WHITE); 
                } else if (map[i][j].value == 0) {
                    DrawTextureRec(SPRITE_SHEET, (Rectangle){tile_size + 1,tile_start, tile_size, tile_size} , (Vector2){tile_size * i, tile_size * j}, WHITE); 
                } else if (map[i][j].value == -1) {
                    DrawTextureRec(SPRITE_SHEET, (Rectangle){bomb_start.x,bomb_start.y, tile_size, tile_size} , (Vector2){tile_size * i, tile_size * j}, WHITE); 
                } else {
                    DrawTextureRec(SPRITE_SHEET, (Rectangle){ (map[i][j].value - 1) * 17,number_tile_start, tile_size, tile_size} , (Vector2){tile_size * i, tile_size * j}, WHITE); 
                }
            }
        }
        
}

void init() {
    canvas = LoadRenderTexture(designWidth, designHeight);
    SPRITE_SHEET = LoadTexture("assets/spritesheet.png");
    generateGameGrid();
}

void update() {
    currentW = GetScreenWidth();
    currentH = GetScreenHeight();
    float wScale = currentW / (float)SCREEN_WIDTH;
    float hScale = currentH / (float)SCREEN_HEIGHT;
    if (wScale < hScale) { scale = wScale; } else { scale = hScale; }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        updateCursorControl();
    }
}

void draw() {
    BeginTextureMode(canvas);
        ClearBackground(BLACK);
        DrawText("valami", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 30, WHITE);
        drawGameGrid();
    EndTextureMode();


    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(canvas.texture, (Rectangle){0,0, canvas.texture.width, -canvas.texture.height}, (Rectangle){0,0, SCREEN_WIDTH  * scale, SCREEN_HEIGHT * scale}, (Vector2){0,0}, 0, WHITE);
    EndDrawing();

}

