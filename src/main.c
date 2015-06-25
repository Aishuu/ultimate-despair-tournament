#include "game/game.h"
#include "init_player.h"
#include "game/gui.h"
#include "Aishuu/ANN.h"

#include "include.h"

int fightPlayer (getThetaFunction (*init_1)(const Game, void *), getThetaFunction (*init_2)(const Game, void *), void * arg1, void * arg2, char isGUI) {
    srand(clock());

    Game game = game_new_game ();
    char newTheta_1, newTheta_2;
    clock_t delay, t = clock ();

    if (isGUI)
        initGUI ();

    getThetaFunction getTheta1 = init_1 (game, arg1);
    getThetaFunction getTheta2 = init_2 (game, arg2);

    while (!game->won) {
        if (isGUI && getEvent () == -1)
            break;
        newTheta_1 = (*getTheta1) (game, arg1);
        newTheta_1 = (newTheta_1 > 0 ? 1 : newTheta_1 == 0 ? 0 : -1);
        newTheta_2 = (*getTheta2) (game, arg2);
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

    int r = fightPlayer (initTheDemos, initAishuu, NULL, NULL, 1);

    if (r == 0)
        printf ("Match interrupted.\n");
    else if (r > 2)
        printf ("Match nul...\n");
    else
        printf ("%s won !\n", players[r-1]);

    return r;
}

#define POP_SIZE        100
#define NB_MATCH        99
#define MATCH_KILL_RATE 0.7
#define MUTATION_RATE   0.2
#define MAX_MUTATION    10
#define GENE_PER_DISP   500

int trainANN (int maxGen) {
    ANN anns_1[POP_SIZE];
    ANN anns_2[POP_SIZE];

    clock_t time;
    clock_t debut = clock();

    ANN *anns = anns_1, *anns_bak = anns_2, *tmp;

    int i;
    for (i=0; i<POP_SIZE; i++)
        anns_1[i] = ANN_new_ANN ();

    int gen;
    for (gen=0; gen<maxGen || maxGen == 0; gen++) {
        int contestantsAlive = POP_SIZE;
        for (i=0; i<NB_MATCH && contestantsAlive > 1; i++) {

            time = clock();
            printf ("\r[% 10lds] Generation % 4d", (time - debut) / CLOCKS_PER_SEC, gen);
            fflush (stdout);

            int contestants[2];
            do {
                do {
                    contestants[0] = rand () % POP_SIZE;
                } while (anns[contestants[0]] == NULL);
                do {
                    contestants[1] = rand () % POP_SIZE;
                } while (anns[contestants[1]] == NULL);
            } while (contestants[0] == contestants[1]);
            
            int r = fightPlayer (initAishuu, initAishuu, (void *) anns[contestants[0]], (void *) anns[contestants[1]], 0);
            if (r == 1 || r == 2) {
                int mort = rand () % 1000;
                if (mort < MATCH_KILL_RATE * 1000) {
                    contestantsAlive --;
                    ANN_free_ANN (anns[contestants[2-r]]);
                    anns[contestants[2-r]] = NULL;
                }
            }
        }

        int j=0;
        for (i=0; i<POP_SIZE; i++)
            if (anns[i] != NULL)
                anns_bak[j++] = anns[i];


        time = clock();
        printf ("\r[% 10lds] Generation % 4d", (time - debut) / CLOCKS_PER_SEC, gen);
        fflush (stdout);

        for (i=contestantsAlive; i<POP_SIZE; i++) {
            int contestants[2];
            do {
                contestants[0] = rand () % contestantsAlive;
                contestants[1] = rand () % contestantsAlive;
            } while (contestants[0] == contestants[1]);

            anns_bak[i] = ANN_mate_ANN (anns_bak[contestants[0]], anns_bak[contestants[1]]);
        }

        for (i=0; i<POP_SIZE; i++) {
            int mutation = rand () % 1000;
            if (mutation < MUTATION_RATE * 1000) {
                mutation = (rand () % MAX_MUTATION) + 1;
                ANN_mutate_ANN (anns_bak [i], mutation);
            }
        }

        if (gen % GENE_PER_DISP == 0) {
            int contestants[2];
            do {
                contestants[0] = rand () % contestantsAlive;
                contestants[1] = rand () % contestantsAlive;
            } while (contestants[0] == contestants[1]);
            fightPlayer (initAishuu, initAishuu, (void *) anns_bak[contestants[0]], (void *) anns_bak[contestants[1]], 1);
        }

        tmp = anns;
        anns = anns_bak;
        anns_bak = tmp;

        time = clock();
        printf ("\r[% 10lds] Generation % 4d", (time - debut) / CLOCKS_PER_SEC, gen);
        fflush (stdout);
    }

    return gen;
}

int main (int argc, char ** argv) {
    return trainANN (0);
    //return realTournament ();
}
