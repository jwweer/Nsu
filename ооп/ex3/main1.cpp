#include <iostream>
#include <memory>

int main() {
    int* a = new int(42);
    int* b = new int[5] {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n" << *a << "\n";

    int* d = new int(10);
    delete d; // память освобождается, но указатель остается

    int* e = new int(7); // может занять ту же память
    std::cout << "d = " << d << ", e = " << e << "\n";
    delete e;
    d = nullptr; // обнуляем

    const int n = 5;
    const int m = n + 1;
    int* f = new int[m];
    int mid = n / 2;
    for (int i = 0; i < mid; ++i) f[i] = b[i];
    f[mid] = 999;
    for (int i = mid; i < n; ++i) f[i + 1] = b[i]; // сдвиг вправо

    for (int i = 0; i < m; ++i) std::cout << f[i] << " ";
    std::cout << "\n";

    delete a;
    delete[] b;
    delete[] f; // очищение памяти
    a = nullptr;
    b = nullptr;
    f = nullptr;

    std::unique_ptr<int> u = std::make_unique<int>(17);
    std::cout << *u << "\n";

    std::shared_ptr<int> s1 = std::make_shared<int>(77);
    std::cout << *s1 << "\n";
    std::cout << s1.use_count() << "\n";

    return 0;
}