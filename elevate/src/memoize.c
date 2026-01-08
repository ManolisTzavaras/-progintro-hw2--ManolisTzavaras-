#include <stdio.h>
#include <stdlib.h>
#include "elevate.h"

// Reference: 6-7
static int **memo_table = NULL;

int Recursive_memo(int stops, int biggest, int dests[], int numPeople) {
    if (stops == 0) {
        return fw(0, -1, dests, numPeople);
    }
    if (memo_table[stops][biggest] != -1) {
        return memo_table[stops][biggest];
    }

    int min_val = -1;
    for (int k = 0; k <= biggest; k++) {
        int cost = Recursive_memo(stops - 1, k, dests, numPeople) - fw(k, -1, dests, numPeople) + fw(k, biggest, dests, numPeople) + fw(biggest, -1, dests, numPeople);
        if (min_val == -1 || cost < min_val) {
            min_val = cost;
        }
    }
    memo_table[stops][biggest] = min_val;
    return min_val;
}

void Memoize_implementation(int numStops, int numFloors, int dests[], int numPeople) {
    memo_table = malloc((numStops + 1) * sizeof(int *));
    for (int i = 0; i <= numStops; i++) {
        memo_table[i] = malloc((numFloors + 1) * sizeof(int));
        for (int j = 0; j <= numFloors; j++) {
            memo_table[i][j] = -1;
        }
    }

    int minCosts = -1;
    int LastFloor = 0;
    for (int biggest = 0; biggest <= numFloors; biggest++) {
        int cost = Recursive_memo(numStops, biggest, dests, numPeople);
        if (minCosts == -1 || cost < minCosts) {
            minCosts = cost;
            LastFloor = biggest;
        }
    }

    printf("Last stop at floor: %d\n", LastFloor);
    printf("The minimum cost is: %d\n", minCosts);

    for (int i = 0; i <= numStops; i++) {
        free(memo_table[i]);
    }
    free(memo_table);
}
