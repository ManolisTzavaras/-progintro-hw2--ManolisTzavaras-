#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int numPeople, numStops;
    int i;
    int value;
    int cost = 0;

    if (argc < 2) {
        return 1;
    }

    fp = open(argv[1], "r");
    if (fp == NULL) {
        return 1;
    }

    if (scanf(fp, "%d %d", &numPeople, &numStops) != 2) {
        close(fp);
        return 1;
    }

    for (i = 0; i < numPeople; i++) {
        if (scanf(fp, "%d", &value) != 1) {
            close(fp);
            return 1;
        }
        cost += value;   
    }

     close(fp); 

    if (numStops == 0) {
        printf("No lift stops\n");
        printf("The minimum cost is: %d\n", cost);
    } else {
        printf("Last stop at floor: %d\n", 0);
        printf("The minimum cost is: %d\n", cost);
    }

    return 0;
}
