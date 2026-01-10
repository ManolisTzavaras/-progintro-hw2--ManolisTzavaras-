#include <stdio.h>
#include <stdlib.h>
#include "elevate.h"

static int **memo = NULL;

int Recursive_memo(int stops, int j, int dests[], int numPeople) {
    if (stops == 0) {
        return fw(0, -1, dests, numPeople);
    }
    if (memo[stops][j] != -1) {
        return memo[stops][j];
    }
    int min_v = -1;
    for (int k = 0; k <= j; k++) {
        int cost = Recursive_memo(stops - 1, k, dests, numPeople) - fw(k, -1, dests, numPeople) + fw(k, j, dests, numPeople) + fw(j, -1, dests, numPeople);
        if (min_v == -1 || cost < min_v) {
            min_v = cost;
        }
    }
    memo[stops][j] = min_v;
    return min_v;
}

void Memoize_implementation(int numStops, int numFloors, int dests[], int numPeople) {
    memo = malloc((numStops + 1) * sizeof(int *));
    for (int i = 0; i <= numStops; i++) {
        memo[i] = malloc((numFloors + 1) * sizeof(int));
        for (int j = 0; j <= numFloors; j++) {
            memo[i][j] = -1;
        }
    }
    int minC = -1;
    int lastF = 0;
    for (int j = 0; j <= numFloors; j++) {
        int cost = Recursive_memo(numStops, j, dests, numPeople);
        if (minC == -1 || cost < minC) {
            minC = cost;
            lastF = j;
        }
    }
    if (minC == fw(0, -1, dests, numPeople)) {
        printf("No lift stops\n");
    } else {
        printf("Last stop at floor: %d\n", lastF);
    }
    printf("The minimum cost is: %d\n", minC);
    for (int i = 0; i <= numStops; i++) {
        free(memo[i]);
    }
    free(memo);
}
