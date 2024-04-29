#include "global.h"
#include "game.h"
#include "raylib.h"
#include <stdio.h>
#include "ui.h"

const int padding = 5;
const int side_padding = 15;

const Vector2 num_size = {13,23};
const Vector2 emoji_size = {24,24};

int centerX;
int centerY;
int num_width;

int decor_height;

void draw_numbers(int number, int start_x) {
    char buff[4];
    sprintf(buff,"%3d", number);

    for (int i = 0; i < 3; ++i) {
        int val = buff[i] - '0';                            
        const Rectangle to = { start_x + num_width * i, padding, num_width, decor_height};
        // It was a space, we draw a zero
        if (val == -16 || val == 0) {
            const Rectangle from = {126, 0, num_size.x, num_size.y};
            DrawTexturePro(SPRITE_SHEET, from, to, (Vector2){0,0},0,WHITE);
        } else {
            const Rectangle from = {
                (num_size.x + 1) * (val - 1), 0, num_size.x, num_size.y};
            DrawTexturePro(SPRITE_SHEET, from, to, (Vector2){0,0},0,WHITE);
        }
    }
}

void draw_top_bar(Game *game) {
    num_width = num_size.x * (decor_height / num_size.y);
    centerX = game->window_w / 2;
    centerY = game->field_start / 2;
    
    decor_height = game->field_start - (padding * 2);

    const Rectangle emoji = {0,24 ,emoji_size.x, emoji_size.y};
    const Rectangle emoji_to = { 
         centerX - decor_height/2,
         centerY - decor_height/2,
         decor_height,
         decor_height,
    };
    // Draw middle emoji
    DrawTexturePro(SPRITE_SHEET,
            emoji,
            emoji_to,
            (Vector2){0,0},
            0,
            WHITE);


    draw_numbers((int)game->time, side_padding);
    draw_numbers(game->bomb_count, game->window_w - side_padding - 3*num_width);

    // center the emoji
    //
    // draw the time and get the sprites from the spritesheet
    // draw background??


    // set bg color to minesweeper bg
}


