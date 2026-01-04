#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "elevate.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    int numPeople;
    int numStops;

    if (fscanf(file, "%d", &numPeople) != 1) {
        fclose(file);
        return 1;
    }

    if (fscanf(file, "%d", &numStops) != 1) {
        fclose(file);
        return 1;
    }

    int *pinakas = malloc(numPeople * sizeof(int));
    if (pinakas == NULL) {
        fclose(file);
        return 1;
    }

    int dest;
    int numFloors = 0;

    for (int i = 0; i < numPeople; i++) {
        if (fscanf(file, "%d", &dest) != 1) {
            free(pinakas);
            fclose(file);
            return 1;
        }
        pinakas[i] = dest;
        if (dest > numFloors) {
            numFloors = dest;
        }
    }
    fclose(file);

    if (strcmp(argv[2], "--mode=recurse") == 0) {
        if (numStops == 0) {
            printf("No lift stops\n");
            printf("The minimum cost is: %d\n", fw(0, -1, pinakas, numPeople));
        } else {
            int min_cost = -1;
            int lastFloor = 0;
            for (int j = 1; j <= numFloors; j++) {
                int cost = Recursive(numStops, j, pinakas, numPeople);
                if (min_cost == -1 || cost < min_cost) {
                    min_cost = cost;
                    lastFloor = j;
                }
            }
            printf("Last stop at floor: %d\n", lastFloor);
            printf("The minimum cost is: %d\n", min_cost);
        }
    } 
    else if (strcmp(argv[2], "--mode=brute") == 0) {
        solve_brute(numStops, numFloors, pinakas, numPeople);
    } 
    else if (strcmp(argv[2], "--mode=memoize") == 0) {
        if (numStops == 0) {
            printf("No lift stops\n");
            printf("The minimum cost is: %d\n", fw(0, -1, pinakas, numPeople));
        } else {
            solve_memoize(numStops, numFloors, pinakas, numPeople);
        }
    }

    free(pinakas);
    return 0;
}
