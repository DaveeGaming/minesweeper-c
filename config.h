#include "game.h"

#ifndef CONFIG_HPP

    #define CONFIG_HPP

    typedef struct Configs {
        int width;
        int height;
        double bomb_chance;
        double ui_scale;
    } Config;


    Config load_config();
    void apply_config(Config *config, Game *game);

#endif // CONFIG_HPP
