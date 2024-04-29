#include "game.h"
#include "raylib.h"
#include "global.h"
#include <stdlib.h>
#include "field.h"

void draw_field(Game *game) {
        const int tile_start = 49;
        const int number_tile_start = 66;
        
        const int draw_size = SPRITE_SIZE * game->ui_scale;

        for (int i = 0; i < game->height; ++i) {
            for (int j = 0; j < game->width; ++j) {
                Rectangle from = {0, 0, SPRITE_SIZE, SPRITE_SIZE};
                Rectangle to = {draw_size * i,game->field_start + draw_size * j, draw_size, draw_size};
                if (game->map[i][j].hidden) {
                    // TILE NOT REVEALED YET

                    // TILE FLAGGED
                    if (game->map[i][j].flag) {
                        from = (Rectangle){34,49, SPRITE_SIZE, SPRITE_SIZE};
                    } else {
                        from = (Rectangle){0,tile_start, SPRITE_SIZE, SPRITE_SIZE};
                    }
                } else if (game->map[i][j].value == 0) {
                    // TILE REVEALED AND EMPTY
                    from = (Rectangle){SPRITE_SIZE + 1,tile_start, SPRITE_SIZE, SPRITE_SIZE};
                } else if (game->map[i][j].value == -1) {
                    // TILE REVEALED AND BOMB
                    from = (Rectangle){85,49, SPRITE_SIZE, SPRITE_SIZE};
                } else {
                    // TILE REVEALED AND SOME VALUE FROM 1 TO 9
                    from = (Rectangle){ (game->map[i][j].value - 1) * 17,number_tile_start, SPRITE_SIZE, SPRITE_SIZE};
                }
                DrawTexturePro(SPRITE_SHEET, from, to, (Vector2){0,0}, 0, WHITE);
            }
        }
        
}

Tile default_tile() {
    return (Tile){
        .hidden = true,
        .flag = false,
        .value = 0,
    };
}

void generate_field(Game *game) {
    game->map = malloc(game->height * sizeof(Tile*) );
    for (int i = 0; i < game->height; ++i) {
        game->map[i] = malloc(game->width * sizeof(Tile) );
        for (int j = 0; j < game->width; ++j) {
            game->map[i][j] = default_tile();
        }
    }

    for (int i = 0; i < game->height; ++i) {
        for (int j = 0; j < game->width; ++j) {
            int random = rand() % 10; // 0-9
            if (!random) {
                game->bomb_count += 1;
                game->map[i][j].value = -1;
                increment_neighbour(game, i, j);
            }
        }
    }
    //EASIEST IS IF YOU INCREMENT THE NEIGHBOURS WHEN U PLACE A BOMB
    //so we dont have to loop through it twice
}

void regenerate_field(Game *game, int new_width,int new_height) {
    for (int i = 0; i < game->height; ++i) {
        free(game->map[i]); 
    }
    free(game->map);
    game->width = new_width;
    game->height = new_height;
    generate_field(game);
}

void increment_neighbour(Game *game, int x, int y) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (tile_exists(game, x + i, y + j)) {
                if (game->map[x + i][y + j].value != -1) {
                    game->map[x + i][y + j].value += 1;
                } 
            } 
        }
    }
}

bool tile_exists(Game *game, int x, int y) {
    return (
        x >= 0 && y >= 0 
        && x < game->width
        && y < game->height);
}

void flag_tile(Game *game, int x, int y) {
    if (tile_exists(game, x,y)) {
        game->map[x][y].flag = !game->map[x][y].flag;
    }
}

void reveal_tile(Game *game, int x, int y) {
    // Check for bomb first
    if (tile_exists(game, x,y) && game->map[x][y].value == -1) {
        // IT was a bomb, you are fucked
    }
    // It was not, reveal tile and neighbours
    reveal_tile_rec(game, x,y );
}

void reveal_tile_rec(Game *game, int x, int y) {
    // If tile is out of bounds, return
    if (!tile_exists(game, x, y)) { return;  }

    // If tile is flagged, return
    if (game->map[x][y].flag) { return; }

    // If tile is not hidden, reveal it
    if (game->map[x][y].hidden && game->map[x][y].value > -1) { game->map[x][y].hidden = false; }
    // alredy revealed TODO: reveal neighbours if flags are set correctly
    else { return; }



    // If this tile is empty, reveal it's neighbours
    if (game->map[x][y].value == 0) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i != 0 || j != 0) {
                reveal_tile_rec(game, x + i, y + j); 
            }
        }
    }
    }
}

