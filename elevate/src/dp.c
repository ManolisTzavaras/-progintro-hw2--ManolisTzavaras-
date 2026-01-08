
#include <stdio.h>
#include <stdlib.h>
#include "elevate.h"



void solve_dp(int numStops, int numFloors, int dests[], int numPeople, int debug) {
    int **dip_gia_dip = malloc((numStops + 1) * sizeof(int *));
    int **parent_ptr = malloc((numStops + 1) * sizeof(int *));
    
    for (int i = 0; i <= numStops; i++) {
        dip_gia_dip[i] = malloc((numFloors + 1) * sizeof(int));
        parent_ptr[i] = malloc((numFloors + 1) * sizeof(int));
    }

    for (int j = 0; j <= numFloors; j++) {
        dip_gia_dip[0][j] = fw(0, -1, dests, numPeople);
    }

    for (int i = 1; i <= numStops; i++) {
        for (int j = 0; j <= numFloors; j++) {
            dip_gia_dip[i][j] = -1;
            for (int k = 0; k <= j; k++) {
                int cost = dip_gia_dip[i-1][k] - fw(k, -1, dests, numPeople) + fw(k, j, dests, numPeople) + fw(j, -1, dests, numPeople);
                if (dip_gia_dip[i][j] == -1 || cost < dip_gia_dip[i][j]) {
                    dip_gia_dip[i][j] = cost;
                    parent_ptr[i][j] = k;
                }
            }
        }
    }

    int minCost = -1;
    int lastFloor = 0;
    for (int j = 0; j <= numFloors; j++) {
        if (minCost == -1 || dip_gia_dip[numStops][j] <= minCost) {
            minCost = dip_gia_dip[numStops][j];
            lastFloor = j;
        }
    }

    if (debug != 0) {
        for (int i = 0; i <= numStops; i++) {
            for (int j = 0; j <= numFloors; j++) {
                printf("%d ", dip_gia_dip[i][j]);
            }
            printf("\n");
        }
        printf("Lift stops are:");
        int *path = malloc(numStops * sizeof(int));
        int curr = lastFloor;
        for (int i = numStops; i > 0; i--) {
            path[i-1] = curr;
            curr = parent_ptr[i][curr];
        }
        for (int i = 0; i < numStops; i++) {
            if (path[i] > 0) {
                printf(" %d", path[i]);
            }
        }
        printf("\n");
        free(path);
    } else {
        printf("Last stop at floor: %d\n", lastFloor);
    }
    printf("The minimum cost is: %d\n", minCost);

    for (int i = 0; i <= numStops; i++) {
        free(dip_gia_dip[i]);
        free(parent_ptr[i]);
    }
    free(dip_gia_dip);
    free(parent_ptr);
}
