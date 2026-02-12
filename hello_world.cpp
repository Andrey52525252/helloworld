#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

int main() {
    
    std::cout << "hello, world" << std::endl;

    int* a = new int(52);

    int* array = new int[10];
    std::cout << array[11] << std::endl;

    int x;
    std::cout << x << std::endl;

    int* p1 = new int;
    free(p1);


    return 0;
}
