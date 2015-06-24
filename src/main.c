#include "game/game.h"
#include "init_player.h"
#include "game/gui.h"

#include "include.h"

int fightPlayer (getThetaFunction (*init_1)(const Game), getThetaFunction (*init_2)(const Game), char isGUI) {
    srand(clock());

    Game game = game_new_game ();
    char newTheta_1, newTheta_2;
    clock_t delay, t = clock ();

    if (isGUI)
        initGUI ();

    getThetaFunction getTheta1 = init_1 (game);
    getThetaFunction getTheta2 = init_2 (game);

    while (!game->won) {
        if (isGUI && getEvent () == -1)
            break;
        newTheta_1 = (*getTheta1) (game);
        newTheta_1 = (newTheta_1 > 0 ? 1 : newTheta_1 == 0 ? 0 : -1);
        newTheta_2 = (*getTheta2) (game);
        newTheta_2 = (newTheta_2 > 0 ? 1 : newTheta_2 == 0 ? 0 : -1);

        game_update_game (game, newTheta_1, newTheta_2);

        if (isGUI) {
            delay = clock();
            if ((delay - t) * IMAGES_PER_SEC < CLOCKS_PER_SEC) {
                struct timespec ts = {0,  (1000 / IMAGES_PER_SEC - (delay - t) * 1000 / CLOCKS_PER_SEC) * 1000000};
                nanosleep (&ts, NULL);
            }
            draw (game);
            t = clock ();
        }
    }

    int r = game->won;

    if (isGUI)
        quitGUI ();

    game_free_game (game);

    return r;
}

int realTournament () {
    const char * players[2] = {PLAYER1, PLAYER2};

    int r = fightPlayer (initTheDemos, initAishuu, 1);

    if (r == 0)
        printf ("Match interrupted.\n");
    else if (r > 2)
        printf ("Match nul...\n");
    else
        printf ("%s won !\n", players[r-1]);

    return r;
}

int main (int argc, char ** argv) {
    return realTournament ();
}
