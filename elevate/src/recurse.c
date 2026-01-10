#include <stdio.h>
#include "elevate.h"

int fw(int a, int b, int dests[], int numPeople) {
    int cost = 0;
    for (int i = 0; i < numPeople; i++) {
        if (dests[i] > a && (b == -1 || dests[i] <= b)) {
            if (b == -1) {
                cost += (dests[i] - a);
            } else {
                int dist_a = dests[i] - a;
                int dist_b = b - dests[i];
                if (dist_a < dist_b) {
                    cost += dist_a;
                } else {
                    cost += dist_b;
                }
            }
        }
    }
    return cost;
}

int Recursive(int stops, int j, int dests[], int numPeople) {
    if (stops == 0) {
        return fw(0, -1, dests, numPeople);
    }
    int min_cost = -1;
    for (int k = 0; k <= j; k++) {
        int cost = Recursive(stops - 1, k, dests, numPeople) - fw(k, -1, dests, numPeople) + fw(k, j, dests, numPeople) + fw(j, -1, dests, numPeople);
        if (min_cost == -1 || cost < min_cost) {
            min_cost = cost;
        }
    }
    return min_cost;
}

void Recursive_implementation(int numStops, int numFloors, int dests[], int numPeople) {
    int minCost = -1;
    int lastFloor = 0;
    for (int j = 0; j <= numFloors; j++) {
        int cost = Recursive(numStops, j, dests, numPeople);
        if (minCost == -1 || cost < minCost) {
            minCost = cost;
            lastFloor = j;
        }
    }
    if (minCost == fw(0, -1, dests, numPeople)) {
        printf("No lift stops\n");
    } else {
        printf("Last stop at floor: %d\n", lastFloor);
    }
    printf("The minimum cost is: %d\n", minCost);
}
