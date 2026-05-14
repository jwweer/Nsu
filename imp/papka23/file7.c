#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

char grid[SIZE][SIZE];
char *words[100];
int wordCount;
char solution[SIZE][SIZE];

struct Position {
    int row, col;
    int isHorizontal;
    int length;
    int wordIdx;
};

struct Position positions[100];
int posCount;

void findPositions() {
    posCount = 0;
    
    for (int r = 0; r < SIZE; r++) {
        int start = -1;
        for (int c = 0; c <= SIZE; c++) {
            if (c < SIZE && grid[r][c] == '-') {
                if (start == -1) start = c;
            } else {
                if (start != -1 && c - start > 1) {
                    positions[posCount].row = r;
                    positions[posCount].col = start;
                    positions[posCount].isHorizontal = 1;
                    positions[posCount].length = c - start;
                    positions[posCount].wordIdx = -1;
                    posCount++;
                }
                start = -1;
            }
        }
    }
    
    for (int c = 0; c < SIZE; c++) {
        int start = -1;
        for (int r = 0; r <= SIZE; r++) {
            if (r < SIZE && grid[r][c] == '-') {
                if (start == -1) start = r;
            } else {
                if (start != -1 && r - start > 1) {
                    positions[posCount].row = start;
                    positions[posCount].col = c;
                    positions[posCount].isHorizontal = 0;
                    positions[posCount].length = r - start;
                    positions[posCount].wordIdx = -1;
                    posCount++;
                }
                start = -1;
            }
        }
    }
}

int canPlace(int posIdx, char *word) {
    struct Position *p = &positions[posIdx];
    if (strlen(word) != p->length) return 0;
    
    for (int i = 0; i < p->length; i++) {
        int r = p->row + (p->isHorizontal ? 0 : i);
        int c = p->col + (p->isHorizontal ? i : 0);
        if (solution[r][c] != 0 && solution[r][c] != word[i]) return 0;
    }
    return 1;
}

void place(int posIdx, char *word, int placeIt) {
    struct Position *p = &positions[posIdx];
    for (int i = 0; i < p->length; i++) {
        int r = p->row + (p->isHorizontal ? 0 : i);
        int c = p->col + (p->isHorizontal ? i : 0);
        if (placeIt) {
            solution[r][c] = word[i];
        } else {
            if (grid[r][c] == '-') solution[r][c] = 0;
        }
    }
}

int solveCrossword(int idx, int usedMask) {
    if (idx == posCount) return 1;
    
    if (positions[idx].wordIdx != -1) {
        return solveCrossword(idx + 1, usedMask);
    }
    
    for (int w = 0; w < wordCount; w++) {
        if (usedMask & (1 << w)) continue;
        if (canPlace(idx, words[w])) {
            place(idx, words[w], 1);
            positions[idx].wordIdx = w;
            if (solveCrossword(idx + 1, usedMask | (1 << w))) return 1;
            positions[idx].wordIdx = -1;
            place(idx, words[w], 0);
        }
    }
    return 0;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    for (int i = 0; i < SIZE; i++) {
        fscanf(in, "%s", grid[i]);
    }
    
    char wordList[1000];
    fscanf(in, "%s", wordList);
    
    char *token = strtok(wordList, ";");
    wordCount = 0;
    while (token) {
        words[wordCount] = (char*)malloc(strlen(token) + 1);
        strcpy(words[wordCount], token);
        wordCount++;
        token = strtok(NULL, ";");
    }
    
    memset(solution, 0, sizeof(solution));
    findPositions();
    solveCrossword(0, 0);
    
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c] == '+') {
                fprintf(out, "+");
            } else if (solution[r][c] != 0) {
                fprintf(out, "%c", solution[r][c]);
            } else {
                fprintf(out, ".");
            }
        }
        fprintf(out, "\n");
    }
    
    fclose(in);
    fclose(out);
    return 0;
}