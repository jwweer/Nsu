#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#pragma comment(linker, "/STACK:50000000")

double parse_expression(const char **s);
double parse_term(const char **s);
double parse_factor(const char **s);

void skip_spaces(const char **s) {
    while (**s && isspace(**s)) (*s)++;
}

double parse_number(const char **s) {
    double num = 0;
    int sign = 1;
    
    if (**s == '-') {
        sign = -1;
        (*s)++;
    }
    
    while (**s && isdigit(**s)) {
        num = num * 10 + (**s - '0');
        (*s)++;
    }
    
    return sign * num;
}

double parse_factor(const char **s) {
    double result;
    
    skip_spaces(s);
    
    if (**s == '(') {
        (*s)++;
        result = parse_expression(s);
        skip_spaces(s);
        if (**s == ')') (*s)++;
    } else if (**s == '-') {
        (*s)++;
        result = -parse_factor(s);
    } else if (**s == '+') {
        (*s)++;
        result = parse_factor(s);
    } else if (isdigit(**s)) {
        result = parse_number(s);
    } else {
        result = 0;
    }
    
    return result;
}

double parse_term(const char **s) {
    double result = parse_factor(s);
    
    while (1) {
        skip_spaces(s);
        char op = **s;
        if (op == '*' || op == '/') {
            (*s)++;
            double b = parse_factor(s);
            if (op == '*') {
                result = result * b;
            } else {
                result = result / b;
            }
        } else {
            break;
        }
    }
    
    return result;
}

double parse_expression(const char **s) {
    double result = parse_term(s);
    
    while (1) {
        skip_spaces(s);
        char op = **s;
        if (op == '+' || op == '-') {
            (*s)++;
            double b = parse_term(s);
            if (op == '+') {
                result = result + b;
            } else {
                result = result - b;
            }
        } else {
            break;
        }
    }
    
    return result;
}

int main() {
    char *expr = (char*)malloc(500001);
    if (!fgets(expr, 500001, stdin)) {
        free(expr);
        return 1;
    }
    
    const char *s = expr;
    double result = parse_expression(&s);
    
    printf("%.20f\n", result);
    
    free(expr);
    return 0;
}