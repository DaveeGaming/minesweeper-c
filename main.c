#include "game.h"
#include "global.h"
#include <stdio.h>

int main(void)
{
    Game game = default_game();
    while (game.playing) {
        fprintf(stderr,"WE GOT HERE\n");
        start_game(&game);
    }
    return 0;
}
