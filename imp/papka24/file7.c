#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TABLE_SIZE (1 << 20)

typedef struct {
    uint64_t occupied : 1;
    uint64_t is_continuation : 1;
    uint64_t is_shifted : 1;
    uint64_t remainder : 16;  // r = 16
} Slot;

Slot table[TABLE_SIZE];
int q = 20;
int r = 16;

uint64_t fnv1a_hash(const char *str) {
    uint64_t hash = 14695981039346656037ULL;
    for (const char *p = str; *p; ++p) {
        hash ^= (uint64_t)(unsigned char)*p;
        hash *= 1099511628211ULL;
    }
    return hash;
}

void get_quotient_remainder(uint64_t hash, uint64_t *quotient, uint64_t *remainder) {
    uint64_t mask = (1ULL << (q + r)) - 1;
    hash &= mask;
    *quotient = hash >> r;
    *remainder = hash & ((1ULL << r) - 1);
}

void insert(const char *str) {
    uint64_t hash = fnv1a_hash(str);
    uint64_t quotient, remainder;
    get_quotient_remainder(hash, &quotient, &remainder);
    
    uint64_t idx = quotient;
    uint64_t start = idx;
    
    while (1) {
        if (!table[idx].occupied) {
            table[idx].occupied = 1;
            table[idx].remainder = remainder;
            break;
        }
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == start) break;
    }
}

int contains(const char *str) {
    uint64_t hash = fnv1a_hash(str);
    uint64_t quotient, remainder;
    get_quotient_remainder(hash, &quotient, &remainder);
    
    uint64_t idx = quotient;
    uint64_t start = idx;
    
    while (1) {
        if (!table[idx].occupied) return 0;
        if (table[idx].remainder == remainder) return 1;
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == start) break;
    }
    return 0;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d %d %d", &q, &r, &n);
    
    memset(table, 0, sizeof(table));
    
    char str[61];
    for (int i = 0; i < n; i++) {
        fscanf(input, "%s", str);
        insert(str);
    }
    
    int m;
    fscanf(input, "%d", &m);
    
    int false_positives = 0;
    for (int i = 0; i < m; i++) {
        fscanf(input, "%s", str);
        if (contains(str)) {
            false_positives++;
        }
    }
    
    fprintf(output, "%d\n", false_positives);
    
    fclose(input);
    fclose(output);
    return 0;
}