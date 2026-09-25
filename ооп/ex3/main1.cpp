#include <iostream>
#include <memory>

int main() {
    int* a = new int(42);
    const int n = 7;
    int* b = new int[n];

    for (int i = 0; i < n; ++i) {
        b[i] = (i + 1) * 10;
        std::cout << b[i] << " ";
    }
    std::cout << "\n" << *a << "\n";

    int* d = new int(100);
    delete d;

    int* e = new int(777);
    std::cout << "d = " << d << ", e = " << e << "\n";
    delete e;
    d = nullptr;

    const int m = n + 1;
    int* f = new int[m];
    int mid = n / 2;
    for (int i = 0; i < mid; ++i) f[i] = b[i];
    f[mid] = 999;
    for (int i = mid; i < n; ++i) f[i + 1] = b[i];

    for (int i = 0; i < m; ++i) std::cout << f[i] << " ";
    std::cout << "\n";

    delete a;
    delete[] b;
    delete[] f;

    {
        std::unique_ptr<int> u = std::make_unique<int>(55);
        std::cout << *u << "\n";
        std::unique_ptr<int> u2 = std::move(u);
        std::cout << (u ? "alive" : "empty") << " " << *u2 << "\n";
    }

    std::weak_ptr<int> w;
    {
        std::shared_ptr<int> s1 = std::make_shared<int>(77);
        std::shared_ptr<int> s2 = s1;
        w = s1;
        std::cout << *s1 << " " << s1.use_count() << "\n";
        s2.reset();
    }
    if (auto l = w.lock())
        std::cout << *l << "\n";
    else
        std::cout << "object is gone\n";

    return 0;
}