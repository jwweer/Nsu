#ifndef HYPOTENUSE_H
#define HYPOTENUSE_H

#include <cmath>

namespace Hypo {

    template <typename T> // переделали функцию с помощью шаблона для того, чтобы на вход могли подаваться переменные любого типа
    T hypotenuse(const T& a, const T& b) {
        return std::sqrt(a * a + b * b);
    }

    template <typename T>
    void hypotenuse_modify(T& a, T& b) {
        T h = std::sqrt(a * a + b * b);
        a = static_cast<T>(h);
        b = static_cast<T>(h);
    }

}
//Изначально у нас была функция в файле hypotenuse.cpp, там две функции, которые принимают разные типы данных изза чего компилятор не ругается
//namespace сделан для того, чтобы у файлов hypotenuse.cpp и hypotenuse_m.cpp были одинаковые названия у функции
//обращение к фуекции в namespace выглядит так int h1 = Hypo::hypotenuse(a, b); здесь мы вызываем из namespace Hypo функцию hypotenuse

#endif