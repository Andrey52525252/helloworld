#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "int_to_binar.cpp"

std::string s2b(const std::string& input);

using namespace std;

union fu {
    float f; 
    unsigned int u; 
}; 

int main() {

    union fu floatint;
    floatint.f = 67117110.00f;
    cout << s2b(floatint.u);
    return 0;
}
