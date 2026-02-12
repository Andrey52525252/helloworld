#include <iostream>
#include <chrono>
int main() {
auto start = std::chrono::high_resolution_clock::now();
for (long i = 1; i < 1000000000; i += 1); // здесь то что вы хотите измерить
auto end = std::chrono::high_resolution_clock::now();
auto nsec = end - start;
std::cout << nsec.count() << " нсек." << std::endl;
return 0;
}
