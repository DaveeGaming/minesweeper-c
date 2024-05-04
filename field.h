#include "game.h"

#ifndef FIELD_HEADER
    #define FIELD_HEADER

    void draw_field(Game *game);
    void generate_field(Game *game);
    void regenerate_field(Game *game, int new_width, int new_height);
    void increment_neighbour(Game *game, int x, int y);
    bool neighbour_correctly_flagged(Game *game, int x, int y);
    Tile default_tile();
    bool check_win(Game* game);
    void unhide_bombs(Game *game);
    void unhide_non_bomb(Game *game);
    void reveal_tile(Game *game, int x, int y);
    void reveal_tile_rec(Game* game, int x, int y);
    void flag_tile(Game *game, int x, int y);
    bool tile_exists(Game *game, int x, int y);

    
#endif //FIELD_HEADER

