#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Внешние символы
extern int symbol0;
extern double symbol1;
extern int* symbol2;
extern int symbol3();
extern int symbol4(int);
extern int symbol5(int, int);
extern double symbol6(double);
extern int (*symbol7)(double);
extern int symbol8;
extern int symbol9;

typedef union {
    int i;
    double d;
    int* ip;
    double* dp;
    int (*fi)(void);
    int (*fi1)(int);
    int (*fi2)(int, int);
    double (*fd1)(double);
} Value;

typedef struct {
    char type[100];
    Value* ptr;
} Symbol;

Symbol symbols[10];

void parse_type(const char* type_str, int index) {
    strcpy(symbols[index].type, type_str);
    
    if (strcmp(type_str, "int symbol0;") == 0) {
        symbols[index].ptr = (Value*)&symbol0;
    } else if (strcmp(type_str, "double symbol1;") == 0) {
        symbols[index].ptr = (Value*)&symbol1;
    } else if (strcmp(type_str, "int *symbol2;") == 0) {
        symbols[index].ptr = (Value*)&symbol2;
    } else if (strcmp(type_str, "int symbol3();") == 0) {
        symbols[index].ptr = (Value*)symbol3;
    } else if (strstr(type_str, "int symbol4(int)") != NULL) {
        symbols[index].ptr = (Value*)symbol4;
    } else if (strstr(type_str, "int symbol5(int, int)") != NULL) {
        symbols[index].ptr = (Value*)symbol5;
    } else if (strstr(type_str, "double symbol6(double)") != NULL) {
        symbols[index].ptr = (Value*)symbol6;
    } else if (strstr(type_str, "int (*symbol7)(double)") != NULL) {
        symbols[index].ptr = (Value*)&symbol7;
    } else if (strcmp(type_str, "int symbol8;") == 0) {
        symbols[index].ptr = (Value*)&symbol8;
    } else if (strcmp(type_str, "int symbol9;") == 0) {
        symbols[index].ptr = (Value*)&symbol9;
    }
}

Value get_value(int idx) {
    if (strstr(symbols[idx].type, "int *") != NULL) {
        return *(Value*)(*(int**)symbols[idx].ptr);
    }
    if (strstr(symbols[idx].type, "double *") != NULL) {
        return *(Value*)(*(double**)symbols[idx].ptr);
    }
    return *symbols[idx].ptr;
}

int main() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    
    int N, M;
    fscanf(fin, "%d %d", &N, &M);
    fgetc(fin); // Читаем перевод строки
    
    char line[100];
    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), fin);
        line[strcspn(line, "\n")] = 0;
        parse_type(line, i);
    }
    
    for (int q = 0; q < M; q++) {
        int args[3];
        int cnt = 0;
        
        // Читаем запрос
        while (cnt < 3 && fscanf(fin, "%d", &args[cnt]) == 1) {
            cnt++;
        }
        
        if (cnt == 1) {
            // Запрос значения переменной
            Value v = get_value(args[0]);
            if (strstr(symbols[args[0]].type, "double") != NULL) {
                fprintf(fout, "%.15f\n", v.d);
            } else {
                fprintf(fout, "%d\n", v.i);
            }
        } else {
            // Вызов функции
            int func_idx = args[0];
            int arg1_idx = args[1];
            int arg2_idx = (cnt > 2) ? args[2] : -1;
            
            Value arg1 = get_value(arg1_idx);
            Value arg2;
            if (arg2_idx >= 0) arg2 = get_value(arg2_idx);
            
            if (strstr(symbols[func_idx].type, "int (*") != NULL) {
                // Указатель на функцию
                int (*func)(double) = *(int (**)(double))symbols[func_idx].ptr;
                int result = func(arg1.d);
                fprintf(fout, "%d\n", result);
            } else if (strstr(symbols[func_idx].type, "double symbol6") != NULL) {
                double (*func)(double) = (double(*)(double))symbols[func_idx].ptr;
                double result = func(arg1.d);
                fprintf(fout, "%.15f\n", result);
            } else if (strstr(symbols[func_idx].type, "int symbol5") != NULL) {
                int (*func)(int, int) = (int(*)(int, int))symbols[func_idx].ptr;
                int result = func(arg1.i, arg2.i);
                fprintf(fout, "%d\n", result);
            } else if (strstr(symbols[func_idx].type, "int symbol4") != NULL) {
                int (*func)(int) = (int(*)(int))symbols[func_idx].ptr;
                int result = func(arg1.i);
                fprintf(fout, "%d\n", result);
            } else if (strstr(symbols[func_idx].type, "int symbol3") != NULL) {
                int (*func)(void) = (int(*)(void))symbols[func_idx].ptr;
                int result = func();
                fprintf(fout, "%d\n", result);
            }
        }
    }
    
    fclose(fin);
    fclose(fout);
    return 0;
}