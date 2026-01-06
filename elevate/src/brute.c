#include "elevate.h"
#include <stdlib.h>
#include <math.h>

int calCost(int list[], int numStops, int dest[], int numPeople)
{
    int sum = 0;

    for (int i = 0; i < numPeople; i++)
    {
        int cost = dest[i];

        for (int j = 0; j < numStops; j++)
        {
            int current_cost = abs(dest[i] - list[j]);

            if (current_cost < cost)
            {
                cost = current_cost;
            }
            
        }
        sum += cost;
        
    }
    return sum;
    

}

int Brute(int numStops, int numFloors, int dest[],int numPeople)
{

    int * list = calloc(numStops, sizeof(int));

    if (list == NULL)
    {
        printf("Error");
        exit(1);
    }
    
    int * bestList = calloc(numStops, sizeof(int));

    if (bestList == NULL)
    {
        printf("Failure");
        exit(1);    
    }
    
    int minCost = -1



}
