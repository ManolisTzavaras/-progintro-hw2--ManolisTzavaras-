#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elevate.h"



static int g_minCost = -1;
static int *g_bestStops = NULL;

int calCost(int list[], int numStops, int dest[], int numPeople) {
    int sum = 0;
    for (int i = 0; i < numPeople; i++) {
        int min_dist = dest[i]; // Απόσταση από το ισόγειο (0)
        for (int j = 0; j < numStops; j++) {
            int current_dist = abs(dest[i] - list[j]);
            if (current_dist < min_dist) {
                min_dist = current_dist;
            }
        }
        sum += min_dist;
    }
    return sum;
}

void generate_combinations(int startFloor, int k, int current_stops[], int numStops, int numFloors, int dests[], int numPeople) {
    if (k == numStops) {
        int current_cost = calCost(current_stops, numStops, dests, numPeople);
        if (g_minCost == -1 || current_cost < g_minCost) {
            g_minCost = current_cost;
            for (int i = 0; i < numStops; i++) {
                g_bestStops[i] = current_stops[i];
            }
        }
        return;
    }

    for (int i = startFloor; i <= numFloors; i++) {
        current_stops[k] = i;
        generate_combinations(i + 1, k + 1, current_stops, numStops, numFloors, dests, numPeople);
    }
}

void Brute(int numStops, int numFloors, int dests[], int numPeople) {
    g_bestStops = malloc(numStops * sizeof(int));
    int *current_stops = malloc(numStops * sizeof(int));
    g_minCost = -1;

    generate_combinations(1, 0, current_stops, numStops, numFloors, dests, numPeople);

    printf("Lift stops are:");
    for (int i = 0; i < numStops; i++) {
        printf(" %d", g_bestStops[i]);
    }
    printf("\nThe minimum cost is: %d\n", g_minCost);

    free(g_bestStops);
    free(current_stops);
}
