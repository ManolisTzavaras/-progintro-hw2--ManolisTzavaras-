#include <stdio.h>
#include <stdlib.h>
#include "elevate.h"

static int g_minCost = -1;
static int *g_bestStops = NULL;

void generate_combinations(int start, int k, int current[], int numStops, int numFloors, int dests[], int numPeople) {
    if (k == numStops) {
        int cost = 0;
        for (int i = 0; i < numPeople; i++) {
            int min_d = dests[i];
            for (int j = 0; j < numStops; j++) {
                int d = abs(dests[i] - current[j]);
                if (d < min_d) {
                    min_d = d;
                }
            }
            cost += min_d;
        }
        if (g_minCost == -1 || cost < g_minCost) {
            g_minCost = cost;
            for (int i = 0; i < numStops; i++) {
                g_bestStops[i] = current[i];
            }
        }
        return;
    }
    for (int i = start; i <= numFloors; i++) {
        current[k] = i;
        generate_combinations(i + 1, k + 1, current, numStops, numFloors, dests, numPeople);
    }
}

void Brute(int numStops, int numFloors, int dests[], int numPeople) {
    g_bestStops = calloc(numStops, sizeof(int));
    int *current = calloc(numStops, sizeof(int));
    g_minCost = -1;
    generate_combinations(1, 0, current, numStops, numFloors, dests, numPeople);

    if (g_minCost == fw(0, -1, dests, numPeople)) {
        printf("No lift stops\n");
    } else {
        printf("Lift stops are:");
        for (int i = 0; i < numStops; i++) {
            if (g_bestStops[i] > 0) {
                printf(" %d", g_bestStops[i]);
            }
        }
        printf("\n");
    }
    printf("The minimum cost is: %d\n", g_minCost);
    free(g_bestStops);
    free(current);
}
