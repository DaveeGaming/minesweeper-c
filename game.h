#include <raylib.h>

#ifndef GAME_LOOP_HPP
    #define GAME_LOOP_HPP
    
    typedef struct {
        bool hidden, flag; int value;
    } Tile;
    
    typedef struct Games {
        Tile **map;
        int width;
        int height;

        double ui_scale;
        float time;
        int window_w;
        int window_h;

        int field_start;
        int bomb_count;

        int score;
        bool playing;
        bool reset;
    } Game;


    Game default_game();

    void close_game(Game *game);
    void start_game(Game *game);
    void init_game(Game *game);
    void main_loop(Game *game);
    void update(Game *game);
    void draw(Game *game);

#endif //GAME_LOOP_HPP
