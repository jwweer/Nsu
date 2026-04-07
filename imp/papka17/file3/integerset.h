#ifndef INTEGERSET_H
#define INTEGERSET_H

typedef struct IntegerSet IntegerSet;

// Создаёт множество из массива чисел
// Возвращает NULL, если есть дубликаты
IntegerSet* CreateSet(const int* arr, int size);

// Проверяет, содержится ли число в множестве
// Если set == NULL, возвращает 0 (пустое множество)
int IsInSet(const IntegerSet* set, int value);

#endif