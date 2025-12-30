#include <stdio.h>
#include <string.h>

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

        if (dest > numFloors)
        {
            numFloors > dest; 

        }
        
        pinakas[i] = dest;


    }
    


    fclose(file);

    if (!strcmp(argv[2], "--mode=recurse"))
    {
        
        if (numStops > 0)
        {
            int min_cost = -1;
            int lastFloor = 0;

            for (int j = 0; j <= numFloors; j++)
            {
                int cost = Recursive(numStops, j, pinakas, numPeople);

                if(cost < min_cost || min_cost == -1)
                {

                    min_cost = cost;
                    lastFloor = j;


                }

            }
            printf("Last stop at floor : %d\n", lastFloor);
            printf("The minimum cost is : %d\n", min_cost);

        }

        if (numStops == 0)
        {
            printf("No lift stops ");


        }
        
        

    }
    
    

    return 0;    
}
