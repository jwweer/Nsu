#include <iostream>
#include <memory>

int main() {
    {
        std::unique_ptr<int> uptr = std::make_unique<int>(55);
        std::cout << *uptr << "\n";
    }

    {
        std::shared_ptr<int> sptr1 = std::make_shared<int>(77);
        std::shared_ptr<int> sptr2 = sptr1;
        std::cout << *sptr1 << " " << sptr1.use_count() << "\n";
        sptr2.reset();
        std::cout << sptr1.use_count() << "\n";
    }

    return 0;
}