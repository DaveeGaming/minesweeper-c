#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "toml.h"


int extract_int(toml_table_t *table, const char *key) {
    toml_datum_t data = toml_int_in(table, key);

    if (!data.ok) {
        fprintf(stderr, "Unable to parse %s field!", key);
        exit(-1);
    }

    return data.u.i;
}

double extract_double(toml_table_t *table, const char *key) {
    toml_datum_t data = toml_double_in(table, key);

    if (!data.ok) {
        fprintf(stderr, "Unable to parse %s field!", key);
        exit(-1);
    }

    return data.u.d;
}

Config load_config() {

    FILE *file;
    char errbuf[200];
    file = fopen("config.toml", "r");
    if (!file) {
        // If file doesn't exist, create it
        fprintf(stderr, "Unable to parse config file!");
        exit(-1);
    }

    toml_table_t* conf = toml_parse_file(file,errbuf, sizeof(errbuf) );
    if (!conf) {
        fprintf(stderr, "Unable to parse config file!");
        exit(-1);
    }
    fclose(file);

    toml_table_t* settings = toml_table_in(conf, "settings");
    if (!settings) {
        fprintf(stderr, "Unable to parse config file!");
        exit(-1);
    }

    Config c = {
       .width = extract_int(settings, "width"), 
       .height = extract_int(settings, "height"), 
       .bomb_chance = extract_double(settings, "bomb_chance"),
       .ui_scale = extract_double(settings, "ui_scale"),
    };

    return c;
}

void apply_config(Config *config, Game *game) {
    game->width  = config->width;
    game->height = config->height;
    game->bomb_chance = config->bomb_chance;
    game->ui_scale = config->ui_scale;
}
