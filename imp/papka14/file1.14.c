#include <stdio.h>

long long mod(long long base, long long p, long long mod) { //Возведение в степень по модулю
    long long result = 1;
    base %= mod; //Приводим основание по модулю
    while (p > 0) { //Пока степень больше 0
        if (p & 1) { //Если младший бит степени равен 1
            result = (result * base) % mod; //Умножаем результат на основание
        }
        base = (base * base) % mod; //Возводим основание в квадрат
        p >>= 1; //Сдвигаем степень вправо (делим на 2)
    }
    return result;
}

int main() {
    int T; //Количество тестов
    long long M; //Модуль (простое число)
    scanf("%d %lld", &T, &M); //Вводим количество тестов и модуль

    while (T--) { //Обрабатываем каждый тест
        long long A; //Число для которого ищем обратное
        scanf("%lld", &A); //Читаем число A

        if (A % M == 0) { //Если A делится на M
            printf("-1\n"); //Обратного элемента не существует
        } else {
            long long inverse = mod(A, M - 2, M); //Находим обратный элемент по малой теореме Ферма
            printf("%lld\n", inverse); //Выводим обратный элемент
        }
    }

    return 0;
}