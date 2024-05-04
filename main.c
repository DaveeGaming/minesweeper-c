#include "game.h"
#include "global.h"
#include "config.h"

int main(void)
{
    Config c = load_config();
    Game game = default_game();
    apply_config(&c, &game);

    while (game.playing) {
        start_game(&game);
    }
    return 0;
}
