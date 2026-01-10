#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "elevate.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return 1;
    }

    int numPeople, numStops;
    if (fscanf(file, "%d %d", &numPeople, &numStops) != 2) {
        fclose(file);
        return 1;
    }

    int *dests = malloc(numPeople * sizeof(int));
    if (dests == NULL) {
        fclose(file);
        return 1;
    }

    int numFloors = 0;
    for (int i = 0; i < numPeople; i++) {
        if (fscanf(file, "%d", &dests[i]) != 1) {
            break;
        }
        if (dests[i] > numFloors) {
            numFloors = dests[i];
        }
    }
    fclose(file);

    char *mode = "dp";
    int debug = 0;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--mode=recurse") == 0) {
            mode = "recurse";
        } else if (strcmp(argv[i], "--mode=brute") == 0) {
            mode = "brute";
        } else if (strcmp(argv[i], "--mode=memoize") == 0) {
            mode = "memoize";
        } else if (strcmp(argv[i], "--mode=dp") == 0) {
            mode = "dp";
        }
        
        if (strcmp(argv[i], "--debug") == 0) {
            debug = 1;
        }
    }

    if (strcmp(mode, "recurse") == 0) {
        Recursive_implementation(numStops, numFloors, dests, numPeople);
    } else if (strcmp(mode, "brute") == 0) {
        Brute(numStops, numFloors, dests, numPeople);
    } else if (strcmp(mode, "memoize") == 0) {
        Memoize_implementation(numStops, numFloors, dests, numPeople);
    } else {
        solve_dp(numStops, numFloors, dests, numPeople, debug);
    }

    free(dests);
    return 0;
}
