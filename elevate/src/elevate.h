
#ifndef ELEVATE_H
#define ELEVATE_H

int fw(int a, int b, int dests[], int numPeople);
int Recursive(int stops, int biggest, int dests[], int numPeople);
void solve_brute(int numStops, int maxFloor, int dests[], int numPeople);
void solve_memoize(int numStops, int numFloors, int dests[], int n);

#endif
