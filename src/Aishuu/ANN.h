#ifndef ANN_H
#define ANN_H

#define INPUTS              10
#define OUTPUTS             2
#define LAYER               3
#define NEURONS_PER_LAYER   30

#define MAX_EDGE_VALUE      20
#define MAX_THRESHOLD_VALUE (MAX_EDGE_VALUE*NEURONS_PER_LAYER)

#define NB_EDGES            (INPUTS * NEURONS_PER_LAYER + (LAYER - 1) * NEURONS_PER_LAYER * NEURONS_PER_LAYER + OUTPUTS * NEURONS_PER_LAYER)

typedef struct {
    int edges [NB_EDGES];
    int threshold [NEURONS_PER_LAYER*LAYER+OUTPUTS];
} * ANN;
    
ANN ANN_new_ANN ();
void ANN_free_ANN (ANN ann);
void ANN_compute (ANN ann, int inputs[INPUTS], char outputs[OUTPUTS]);

#endif // ANN_H
