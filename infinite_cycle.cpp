#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "int_to_binar.cpp"
#include <cmath>


std::string s2b(const std::string& input);

using namespace std;

union fu {
    float f; 
    unsigned int u; 
}; 

int main() {

    cout << fixed;
    cout.precision(2);
    float prev = 0;
    
    for (float i = 10000000; i < 100000000; i++)
    {

        cout << "step " << i << std::endl;

        if (i == prev) {
            cout << "broke on number " << i;
            break;
        }
        prev = i;

        if (int(i) % 100 == 0) {
            i += 10001;
        }

    }
    
    return 0;
}
