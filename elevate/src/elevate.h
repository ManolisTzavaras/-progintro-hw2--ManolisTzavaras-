#ifndef ELEVATE_H
#define ELEVATE_H

int fw(int a, int b, int dests[], int numPeople);
int Recursive(int stops, int biggest, int dests[], int numPeople);
void solve_dp(int numStops, int numFloors, int dests[], int n);
void Recursive_implementation(int numStops,int numFloors,int dest[], int numPeople );
void Brute(int numStops,int numFloors,int dest[], int numPeople );
int calCost(int list[], int numStops, int dest[], int numPeople);


#endif
