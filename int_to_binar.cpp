#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

std::string s2b(unsigned int number)
{
    string binar = " ";

    for (int i = 0; i < 32; i ++) {
        if (number == number << 1 >> 1) 
            binar += "0";
        else 
            binar += "1";
        
        number <<= 1;

    }
    cout << endl;
    return binar;
}

int main() {
    cout << s2b(1025);
    return 0;
}
