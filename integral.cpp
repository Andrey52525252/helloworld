#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

int main() {
    // Создаем файл с данными
    std::ofstream datafile("data.csv");

    float integral = 0;


    for (float count = 1; count <= 100; count += 1) {

        float step = 2 / count;
        integral = 0;

        for (float x = -1; x <= 1; x += step) {
            float y = sqrt(1 - x*x);
            integral += step * y;  
        }

        datafile << count << " " << integral << " " << 1.570976 << std::endl;
        std::cout << "count " << count << std::endl;
    }
    datafile.close();

    std::cout << integral;
    
    return 0;
}
