#include <iostream>

int main() {
    int* single = new int(42);
    const int SIZE = 7;
    int* arr = new int[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = (i + 1) * 10;
        std::cout << arr[i] << " ";
    }
    std::cout << "\n" << *single << "\n";

    int* dangling = new int(100);
    delete dangling;
    std::cout << dangling << "\n";

    const int NEW_SIZE = SIZE + 1;
    int* newArr = new int[NEW_SIZE];
    int mid = SIZE / 2;
    for (int i = 0; i < mid; ++i) newArr[i] = arr[i];
    newArr[mid] = 999;
    for (int i = mid; i < SIZE; ++i) newArr[i + 1] = arr[i];

    for (int i = 0; i < NEW_SIZE; ++i) std::cout << newArr[i] << " ";
    std::cout << "\n";

    delete single;
    delete[] arr;
    delete[] newArr;
    dangling = nullptr;

    return 0;
}