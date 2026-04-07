#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL //Модуль для вычислений
#define MAXN 1000000 //Максимальное значение N

typedef long long ll; //Синоним для long long

ll fact[MAXN + 1]; //Массив для факториалов
ll inv_fact[MAXN + 1]; //Массив для обратных факториалов

ll mod_pow(ll a, ll b, ll mod);

int main() {
    int T; //Количество запросов
    fscanf(stdin, "%d", &T); //Читаем количество запросов

    // Считываем все запросы и находим максимальное N
    int *N_arr = (int*)malloc(T * sizeof(int)); //Массив для N
    int *K_arr = (int*)malloc(T * sizeof(int)); //Массив для K
    int maxN = 0; //Максимальное значение N среди запросов

    for (int i = 0; i < T; i++) { //Читаем все запросы
        fscanf(stdin, "%d %d", &N_arr[i], &K_arr[i]); //Читаем пару N, K
        if (N_arr[i] > maxN) { //Обновляем максимальное N
            maxN = N_arr[i];
        }
    }

    // Предвычисление факториалов
    fact[0] = 1; //0! = 1
    for (int i = 1; i <= maxN; i++) { //Вычисляем факториалы для всех i от 1 до maxN
        fact[i] = (fact[i - 1] * i) % MOD; //i! = (i-1)! * i по модулю
    }

    // Предвычисление обратных факториалов
    inv_fact[maxN] = mod_pow(fact[maxN], MOD - 2, MOD); //(maxN)!^(-1) по малой теореме Ферма
    for (int i = maxN; i >= 1; i--) { //Вычисляем обратные факториалы в обратном порядке
        inv_fact[i - 1] = (inv_fact[i] * i) % MOD; //(i-1)!^(-1) = i!^(-1) * i
    }

    // Ответы на запросы
    for (int i = 0; i < T; i++) { //Обрабатываем каждый запрос
        int N = N_arr[i]; //Берем N из запроса
        int K = K_arr[i]; //Берем K из запроса
        ll res = fact[N] * inv_fact[K] % MOD; //N! / K!
        res = res * inv_fact[N - K] % MOD; //(N! / K!) / (N-K)! = C(N,K) по модулю
        fprintf(stdout, "%lld\n", res); //Выводим результат
    }

    free(N_arr); //Освобождаем память
    free(K_arr);
    return 0;
}

// Быстрое возведение в степень по модулю
ll mod_pow(ll a, ll b, ll mod) {
    ll res = 1; //Результат
    while (b > 0) { //Пока степень > 0
        if (b & 1) { //Если младший бит равен 1
            res = (res * a) % mod; //Умножаем результат на a
        }
        a = (a * a) % mod; //Возводим a в квадрат
        b >>= 1; //Сдвигаем степень вправо
    }
    return res; //Возвращаем результат
}