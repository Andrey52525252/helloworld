#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // Проходим по всем элементам n-1 раз
    for (int i = 0; i < n - 1; i++) {
        // Сравниваем соседние элементы
        for (int j = 0; j < n - i - 1; j++) {
            // Если текущий элемент больше следующего, меняем их местами
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < leftArr.size()) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < rightArr.size()) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    mergeSortHelper(arr, 0, arr.size() - 1);
}

void quickSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    
    int pivot = arr[arr.size() / 2];
    int i = 0, j = arr.size() - 1;
    
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    if (j > 0) {
        std::vector<int> left(arr.begin(), arr.begin() + j + 1);
        quickSort(left);
        std::copy(left.begin(), left.end(), arr.begin());
    }
    
    if (i < arr.size()) {
        std::vector<int> right(arr.begin() + i, arr.end());
        quickSort(right);
        std::copy(right.begin(), right.end(), arr.begin() + i);
    }
}

void heapify(std::vector<int>& arr, int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    if (left < size && arr[left] > arr[largest])
        largest = left;
    
    if (right < size && arr[right] > arr[largest])
        largest = right;
    
    if (largest != root) {
        std::swap(arr[root], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int size = arr.size();
    
    // Построение max-heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
    
    // Извлечение элементов из кучи
    for (int i = size - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>
    (std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}


int min_element = 1;
int max_element = 100; // limits of acceptable values in lists


int main(int argc, char* argv[]) {
    std::ofstream file("1.csv", std::ios::app);
    
    // Проверяем открылся ли файл
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file!" << std::endl;
        return 1;
    }
    
    for (int run = 10; run <= 5000; run += 10) {
        int length = run;
        std::vector<int> list(length);

        file << run << " ";

        for (int i = 0; i < length; i++) {
            list[i] = int(i * (max_element - min_element) / length);
        }
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(list);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;
        file << nsec.count() << " ";
        file.flush();  // отсортировали
        

        for (int i = 0; i < length; i++) {
            list[i] = rand_uns(min_element, max_element);
        }
        start = std::chrono::high_resolution_clock::now();
        heapSort(list);
        end = std::chrono::high_resolution_clock::now();
        nsec = end - start;
        file << nsec.count() << " ";
        file.flush();  // рандом


        for (int i = 0; i < length; i++) {
            list[i] = (max_element - min_element) - (i * (max_element - min_element) / length);
        }
        start = std::chrono::high_resolution_clock::now();
        heapSort(list);
        end = std::chrono::high_resolution_clock::now();
        nsec = end - start;
        file << nsec.count() << std::endl;
        file.flush();  // в обратном порядке

        std::cout << "array length: " << run << "; time: " << nsec.count() << " ns" << std::endl;
    }
    
    file << std::endl;
    file.close();
    std::cout << "Data successfully saved to 1.csv" << std::endl;
    return 0;
}

