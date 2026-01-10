#include <stdio.h>
#include <stdlib.h>
#include "elevate.h"

void solve_dp(int numStops, int numFloors, int dests[], int numPeople, int debug) {
    int **dip_gia_dip = malloc((numStops + 1) * sizeof(int *));
    int **parent = malloc((numStops + 1) * sizeof(int *));
    for (int i = 0; i <= numStops; i++) {
        dip_gia_dip[i] = malloc((numFloors + 1) * sizeof(int));
        parent[i] = malloc((numFloors + 1) * sizeof(int));
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
                    parent[i][j] = k;
                }
            }
        }
    }

    int minC = -1;
    int lastF = 0;
    for (int j = 0; j <= numFloors; j++) {
        if (minC == -1 || dip_gia_dip[numStops][j] < minC) {
            minC = dip_gia_dip[numStops][j];
            lastF = j;
        }
    }

    if (debug != 0) {
        for (int i = 0; i <= numStops; i++) {
            for (int j = 0; j <= numFloors; j++) {
                printf("%d%c", dip_gia_dip[i][j], (j == numFloors ? '\n' : ' '));
            }
        }
        if (minC == fw(0, -1, dests, numPeople)) {
            printf("No lift stops\n");
        } else {
            int *path = malloc(numStops * sizeof(int));
            int curr = lastF;
            for (int i = numStops; i > 0; i--) {
                path[i-1] = curr;
                curr = parent[i][curr];
            }
            printf("Lift stops are:");
            for (int i = 0; i < numStops; i++) {
                if (path[i] > 0) {
                    printf(" %d", path[i]);
                }
            }
            printf("\n");
            free(path);
        }
    } else {
        if (minC == fw(0, -1, dests, numPeople)) {
            printf("No lift stops\n");
        } else {
            printf("Last stop at floor: %d\n", lastF);
        }
    }
    printf("The minimum cost is: %d\n", minC);

    for (int i = 0; i <= numStops; i++) {
        free(dip_gia_dip[i]);
        free(parent[i]);
    }
    free(dip_gia_dip);
    free(parent);
}
