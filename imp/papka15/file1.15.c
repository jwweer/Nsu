#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) { //Если нет аргументов командной строки
        fprintf(stderr, "No parameters specified.\n");
        return 13; //Возвращаем код ошибки 13
    }

    long long r; //Переменная для результата
    
    if (argc == 4) { //Формат: <op> <a> <b> (без модуля)
        char op = argv[1][0]; //Первый символ операции (a, s или m)
        long long a = atoll(argv[2]); //Первый операнд
        long long b = atoll(argv[3]); //Второй операнд
        
        if (op == 'a') r = a + b; //Сложение
        else if (op == 's') r = a - b; //Вычитание
        else r = a * b; //Умножение
        
        printf("%lld\n", r); //Выводим результат
        return 0;
    }

    if (argv[1][0] == '-') { //Формат: -m <mod> <op> <a> <b>
        long long m = atoll(argv[2]); //Модуль
        char op = argv[3][0]; //Первый символ операции
        long long a = atoll(argv[4]); //Первый операнд
        long long b = atoll(argv[5]); //Второй операнд
        
        if (op == 'a') r = a + b; //Сложение
        else if (op == 's') r = a - b; //Вычитание
        else r = a * b; //Умножение
        
        r %= m; //Приводим по модулю
        if (r < 0) r += m; //Если отрицательный, делаем положительным
    } 
    else { //Формат: <op> <a> <b> -m <mod>
        char op = argv[1][0]; //Первый символ операции
        long long a = atoll(argv[2]); //Первый операнд
        long long b = atoll(argv[3]); //Второй операнд
        long long m = atoll(argv[5]); //Модуль (индекс 5, так как -m на позиции 4)
        
        if (op == 'a') r = a + b; //Сложение
        else if (op == 's') r = a - b; //Вычитание
        else r = a * b; //Умножение
        
        r %= m; //Приводим по модулю
        if (r < 0) r += m; //Если отрицательный, делаем положительным
    }

    printf("%lld\n", r);
    return 0;
}