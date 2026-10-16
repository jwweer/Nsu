#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Groupmate {
private:
    std::string firstName;
    std::string lastName;
    int age;
    int* marks;
    int marksCount;

    void normalize() {
        auto capitalize = [](std::string& s) {
            if (!s.empty()) {
                s[0] = std::toupper(static_cast<unsigned char>(s[0]));
                for (size_t i = 1; i < s.size(); ++i)
                    s[i] = std::tolower(static_cast<unsigned char>(s[i]));
            }
        };
        capitalize(firstName);
        capitalize(lastName);
        if (age < 16) age = 16;
        if (age > 100) age = 100;
        for (int i = 0; i < marksCount; ++i) {
            if (marks[i] < 2) marks[i] = 2;
            if (marks[i] > 5) marks[i] = 5;
        }
    }

public:
    Groupmate() : firstName("Ivan"), lastName("Ivanov"), age(18), marksCount(0), marks(nullptr) {
        std::cout << "default constructor" << std::endl;
    }

    Groupmate(const std::string& fn, const std::string& ln, int a, const int* m, int count)
        : firstName(fn), lastName(ln), age(a), marksCount(count) {
        marks = new int[marksCount];
        for (int i = 0; i < marksCount; ++i) marks[i] = m[i];
        normalize();
        std::cout << "initialization constructor" << std::endl;
    }

    Groupmate(const Groupmate& other)
        : firstName(other.firstName), lastName(other.lastName), age(other.age),
          marksCount(other.marksCount) {
        marks = new int[marksCount];
        for (int i = 0; i < marksCount; ++i) marks[i] = other.marks[i];
        std::cout << "copy constructor" << std::endl;
    }

    Groupmate& operator=(const Groupmate& other) {
        std::cout << "assignment operator" << std::endl;
        if (this == &other) return *this;
        firstName = other.firstName;
        lastName = other.lastName;
        age = other.age;
        delete[] marks;
        marksCount = other.marksCount;
        marks = new int[marksCount];
        for (int i = 0; i < marksCount; ++i) marks[i] = other.marks[i];
        return *this;
    }

    ~Groupmate() {
        delete[] marks;
    }

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    int getAge() const { return age; }
    int getMarksCount() const { return marksCount; }
    int getMark(int index) const {
        if (index < 0 || index >= marksCount)
            throw std::out_of_range("index out of range");
        return marks[index];
    }

    void setFirstName(const std::string& fn) {
        firstName = fn;
        normalize();
    }

    void setLastName(const std::string& ln) {
        lastName = ln;
        normalize();
    }

    void setAge(int a) {
        age = a;
        normalize();
    }
};