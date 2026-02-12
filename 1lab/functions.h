#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector> 

// Function declarations

void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void selectionSort(std::vector<int>& arr);
double get_time();
int rand_uns(int min, int max);

#endif