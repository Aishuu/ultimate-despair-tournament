#include "include.h"

#include "game.h"
#include "init_player.h"
#include "gui.h"

int main (int argc, char ** argv) {
    srand(clock());

    Game game = game_new_game ();
    char newTheta_1, newTheta_2;
    clock_t delay, t = 0;

    const char * players[2] = {PLAYER1, PLAYER2};

    initGUI ();

    init_player_1 (game);
    init_player_2 (game);

    printf ("game->won: %d\n", game->won);

    while (!game->won) {
        if (getEvent () == -1)
            break;
        newTheta_1 = getTheta_1 (game);
        newTheta_1 = (newTheta_1 > 0 ? 1 : newTheta_1 == 0 ? 0 : -1);
        newTheta_2 = getTheta_2 (game);
        newTheta_2 = (newTheta_2 > 0 ? 1 : newTheta_2 == 0 ? 0 : -1);

        game_update_game (game, newTheta_1, newTheta_2);

        delay = clock();
        if (delay - t < DELAY * CLOCKS_PER_SEC / 1000) {
            struct timespec ts = {.tv_sec = 0,  .tv_nsec = (DELAY - (delay - t)) * 1000 / CLOCKS_PER_SEC};
            nanosleep (&ts, NULL);
        }
        draw (game);
        t = clock ();
    }

    if (game->won == 0)
        printf ("Match interrupted.\n");
    else if (game->won > 2)
        printf ("Match nul...\n");
    else
        printf ("%s won !\n", players[game->won-1]);

    quitGUI ();
    game_free_game (game);

    return 0;
}
