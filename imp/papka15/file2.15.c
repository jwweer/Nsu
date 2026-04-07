#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 205 //Максимальный размер системы
#define EPS  1e-10 //Порог для определения вырожденности

double A[NMAX][NMAX]; //Расширенная матрица системы
double x[NMAX]; //Массив решений

int main(void)
{
    int n, i, j, k; //Размер системы и индексы циклов
    double max_elem, tmp; //Максимальный элемент и временная переменная

    FILE *fin  = fopen("input.txt",  "r"); //Открываем входной файл
    FILE *fout = fopen("output.txt", "w"); //Открываем выходной файл
    if (!fin || !fout) { //Проверка успешности открытия файлов
        if (fin)  fclose(fin);
        if (fout) fclose(fout);
        return 1; //Ошибка открытия файла
    }

    fscanf(fin, "%d", &n); //Читаем размер системы
    for (i = 0; i < n; i++) { //Читаем расширенную матрицу
        for (j = 0; j <= n; j++) {
            fscanf(fin, "%lf", &A[i][j]);
        }
    }
    fclose(fin); //Закрываем входной файл

    //Прямой ход метода Гаусса (с выбором главного элемента)
    for (i = 0; i < n; i++) {
        int pivot = i; //Индекс строки с главным элементом
        max_elem = fabs(A[i][i]); //Текущий главный элемент
        for (k = i + 1; k < n; k++) { //Поиск максимального элемента в столбце
            if (fabs(A[k][i]) > max_elem) {
                max_elem = fabs(A[k][i]);
                pivot = k; //Запоминаем строку с максимальным элементом
            }
        }

        if (pivot != i) { //Если нашли строку с бОльшим элементом
            for (j = 0; j <= n; j++) { //Меняем строки местами
                tmp = A[i][j];
                A[i][j] = A[pivot][j];
                A[pivot][j] = tmp;
            }
        }

        if (fabs(A[i][i]) < EPS) { //Если главный элемент близок к нулю
            fprintf(fout, "System has no unique solution\n"); //Система вырождена
            fclose(fout);
            return 0;
        }

        for (k = i + 1; k < n; k++) { //Исключение переменной из нижних строк
            double factor = A[k][i] / A[i][i]; //Множитель для вычитания
            for (j = i; j <= n; j++) {
                A[k][j] -= factor * A[i][j]; //Вычитаем строку i из строки k
            }
        }
    }

    //Обратный ход метода Гаусса
    for (i = n - 1; i >= 0; i--) { //Движемся снизу вверх
        double sum = 0.0;
        for (j = i + 1; j < n; j++) { //Сумма уже найденных переменных
            sum += A[i][j] * x[j];
        }
        x[i] = (A[i][n] - sum) / A[i][i]; //Вычисляем текущую переменную
    }

    for (i = 0; i < n; i++) { //Выводим результаты
        fprintf(fout, "%.10f\n", x[i]); //С точностью 10 знаков
    }

    fclose(fout); //Закрываем выходной файл
    return 0;