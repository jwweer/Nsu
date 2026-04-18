#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

typedef struct State {
    char *regs[256];
} State;

EXPORT void concat_2(State *state, char *idx0, char *idx1) {
    int i0 = atoi(idx0), i1 = atoi(idx1);
    char *a = state->regs[i0];
    char *b = state->regs[i1];
    if (!a || !b) return;
    
    char *res = malloc(strlen(a) + strlen(b) + 1);
    strcpy(res, a);
    strcat(res, b);
    
    free(state->regs[i0]);
    state->regs[i0] = res;
}

EXPORT void tokenize_1(State *state, char *arg) {
    char *copy = strdup(arg);
    char *token = strtok(copy, "_");
    int count = 0;
    
    while (token) {
        char idx[10];
        sprintf(idx, "%d", count + 1);
        free(state->regs[count + 1]);
        state->regs[count + 1] = strdup(token);
        token = strtok(NULL, "_");
        count++;
    }
    
    char idx0[10] = "0";
    free(state->regs[0]);
    state->regs[0] = malloc(12);
    sprintf(state->regs[0], "%d", count);
    
    free(copy);
}