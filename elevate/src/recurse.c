#include <stdio.h>

int main() {
    int numPeople, numStops;
    int dests[100];
    int cost;

    printf("Enter number of people (max 100): ");
    scanf("%d", &numPeople);

    printf("Enter number of lift stops: ");
    scanf("%d", &numStops);

    printf("Enter destination floors separated by space:\n");
    for(int i = 0; i < numPeople; i++)
        scanf("%d", &dests[i]);

    if(numStops == 0) {
        cost = 0;
        for(int i = 0; i < numPeople; i++)
            cost += dests[i];

        printf("No lift stops\n");
        printf("The minimum cost is: %d\n", cost);
    } else {
        // Demo
        for(int lastStop = 0; lastStop <= 20; lastStop++) {
            cost = 0;
            printf("\nTesting last stop at floor %d\n", lastStop);
            for(int i = 0; i < numPeople; i++) {
                int walk;
                if(dests[i] > lastStop)
                    walk = dests[i] - lastStop;
                else
                    walk = lastStop - dests[i];

                printf(" Passenger %d: destination %d, walk %d\n",
                        i+1, dests[i], walk);

                cost += walk;
            }
            printf(" Total cost: %d\n", cost);
        }
    }

    return 0;
}
