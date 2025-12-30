#include <stdio.h>
int fw(int a, int b, int dests[], int numPeople)
{

    int cost = 0;

    for(int i = 0; i < numPeople; i++)
    {
        if (dests[i] > a && (b == -1 || dests[i] <= b))
        {
         
            if (b == -1)
            {
                
                cost += dests[i] - a;

            }
            else
            {

                int distance_a = dests[i] - a;
                int distance_b = b -dests[i];


                if (distance_a == distance_b)
                {
                    cost += distance_a;
                }
                

                else if (distance_a < distance_b)
                {
                    
                    cost += distance_a;
                }
                else
                {
                    cost += distance_b;

                }
                
                


            }


        }
        


        
    }

    return cost;
}

int RECURSIVE(int stops, int biggest, int dests[], int numPeople)
{



}
