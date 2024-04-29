#include "raylib.h"
#include "game.h"
#include "global.h"
#include "field.h"
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

#undef min
#undef max

int currentW;
int currentH;

float scale;
RenderTexture2D canvas; 



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



Vector2 cursor_click_pos(Game *game) {
    int x = GetMouseX();
    int y = GetMouseY() - (game->field_start * scale);

    // get mouse pos in scaled texture
    x /= scale;
    y /= scale;

    // Get which matrix element the player is clicking on
    x /= 16 * game->ui_scale;
    y /= 16 * game->ui_scale;

    return (Vector2){x, y};
}

Game default_game() {
    // MAP stays null until generated.
    return (Game) {
        .width = 20,
        .height = 20,
        .score = 0,
        .field_start = 50,

        .reset = false,
        .playing = true,
        .ui_scale = 2,
    };
}


void init_game(Game* game) {
    canvas = LoadRenderTexture(game->window_w, game->window_h);
    SPRITE_SHEET = LoadTexture("assets/spritesheet.png");
    generate_field(game);
}

void close_game(Game *game) {
    for (int i = 0; i < game->height; ++i) {
        free(game->map[i]);
    }
    free(game->map);
    CloseWindow();
}

void update(Game *game) {
    game->time += GetFrameTime();


    currentW = GetScreenWidth();
    currentH = GetScreenHeight();
    float wScale = currentW / (float)game->window_w;
    float hScale = currentH / (float)game->window_h;
    if (wScale < hScale) { scale = wScale; } else { scale = hScale; }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = cursor_click_pos(game);
        reveal_tile(game, pos.x, pos.y); 
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 pos = cursor_click_pos(game);
        flag_tile(game, pos.x, pos.y);
    }
    if (WindowShouldClose()) {
        game->playing = false;
    }

    if (IsKeyPressed(KEY_O)) {
        game->ui_scale -= 0.1;
        game->reset = true;
    }
    if (IsKeyPressed(KEY_R)) {
        game->time = 0;
        game->bomb_count = 0;
        regenerate_field(game, game->width, game->height);
    }
    if (IsKeyPressed(KEY_P)) {
        game->ui_scale += 0.1;
        game->reset = true;
    }

}

void start_game(Game *game) {
    game->window_w = game->width * game->ui_scale * SPRITE_SIZE; 
    game->window_h = game->field_start + game->height * game->ui_scale * SPRITE_SIZE; 
    game->time = 0;
    game->bomb_count = 0;
    game->reset = false;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(game->window_w, game->window_h, SCREEN_TITLE);
    SetTargetFPS(60);  

    init_game(game);
    main_loop(game);
}

void main_loop(Game *game) {
    while (!game->reset && game->playing) {
        update(game);
        draw(game);
    }

    if (!game->playing) {
        return;
    } else {
        close_game(game);
        start_game(game);
    }
}

void draw(Game *game) {
    BeginTextureMode(canvas);
        ClearBackground( (Color){192,192,192, 255} );
        draw_top_bar(game);
        draw_field(game);
    EndTextureMode();


    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(canvas.texture,
                (Rectangle){0,0, canvas.texture.width, -canvas.texture.height},
                (Rectangle){0,0, game->window_w  * scale, game->window_h * scale}, 
                (Vector2){0,0},
                0,
                WHITE);
    EndDrawing();

}

