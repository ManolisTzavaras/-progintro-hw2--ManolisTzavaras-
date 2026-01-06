#include <stdio.h>
#include <string.h>
#include "elevate.h"
#include <stdlib.h>

int main(int argc, char * argv[]){


    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        perror("fopen");
        return 1;
    }

    int numPeople;
    int numStops;

    if (fscanf(file, "%d", &numPeople) !=1)
    {
        printf("Failed to read number of people \n");
        return 1;
    }

    if (fscanf(file, "%d", &numStops) !=1)
    {
        printf("Failed to read number of stops \n");
        return 1;
    }

    int *pinakas = malloc(numPeople * sizeof(int));
    
    if (pinakas == NULL)
    {
        fprintf(stderr, "Den uparxei mnimi");
        return 1;
    }
    
    int dest;
    int numFloors = -1;

    for (int i = 0; i < numPeople; i++)
    {
        if(fscanf(file, "%d", &dest) !=1)
        {
            printf("failed to reaf destination: %d\n", i);
            free(pinakas);
            return 1;

        }
 
        if (dest > numFloors || numFloors < 0)
        {
            numFloors = dest; 

        }
        
        pinakas[i] = dest;


    }
    


    fclose(file);

    if (argc > 2)
    {
        if (!strcmp(argv[2], "--mode=recurse"))
        {
            
            Recursive_implementation( numStops, numFloors, pinakas , numPeople);
            

        }
    }
    

 
    
    

    return 0;    
}
