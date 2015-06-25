#include "Aishuu/ANN.h"

#include <stdlib.h>

ANN ANN_new_ANN () {
    ANN ann = (ANN) malloc (sizeof (*ann));

    int i;
    for (i=0; i<NB_EDGES; i++) {
        int r = (rand () % (2*MAX_EDGE_VALUE + 1)) - MAX_EDGE_VALUE;
        ann->edges[i] = r;
    }

    for (i=0; i<NEURONS_PER_LAYER*LAYER+OUTPUTS; i++) {
        int r = (rand () % (2*MAX_THRESHOLD_VALUE + 1)) - MAX_THRESHOLD_VALUE;
        ann->threshold[i] = r;
    }

    return ann;
}

void ANN_free_ANN (ANN ann) {
    free (ann);
}

void ANN_compute (ANN ann, int inputs[INPUTS], char outputs[OUTPUTS]) {
    char neurons [LAYER*NEURONS_PER_LAYER];

    int edge_index = 0;
    int threshold_index = 0;

    int i,j;
    for (i=0; i < NEURONS_PER_LAYER; i++) {
        int acc = 0;
        for (j=0; j < INPUTS; j++)
            acc += ann->edges[edge_index + j]*inputs[j];

        if (acc > ann->threshold[i])
            neurons[i] = 1;
        else
            neurons[i] = 0;

        edge_index += INPUTS;
    }

    threshold_index += NEURONS_PER_LAYER;

    int layer;
    for (layer=1; layer < LAYER; layer++) {
        for (i=0; i < NEURONS_PER_LAYER; i++) {
            int acc = 0;
            for (j=0; j < NEURONS_PER_LAYER; j++)
                acc += ann->edges[edge_index + j]*neurons[threshold_index - NEURONS_PER_LAYER + j];

            if (acc > ann->threshold[threshold_index + i])
                neurons[threshold_index + i] = 1;
            else
                neurons[threshold_index + i] = 0;
            edge_index += NEURONS_PER_LAYER;
        }

        threshold_index += NEURONS_PER_LAYER;
    }

    for (i=0; i < OUTPUTS; i++) {
        int acc = 0;
        for (j=0; j < NEURONS_PER_LAYER; j++)
            acc += ann->edges[edge_index + j]*neurons[threshold_index - NEURONS_PER_LAYER + j];

        if (acc > ann->threshold[threshold_index + i])
            outputs[i] = 1;
        else
            outputs[i] = 0;

        edge_index += NEURONS_PER_LAYER;
    }
}
