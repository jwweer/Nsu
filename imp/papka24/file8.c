#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define P 14
#define M (1 << P)
uint8_t registers[M];

uint32_t ip_to_int(const char *ip) {
    uint32_t a, b, c, d;
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

int leading_zeros(uint32_t hash, int p) {
    hash >>= p;
    int count = 1;
    while ((hash & 1) == 0 && hash != 0) {
        count++;
        hash >>= 1;
    }
    return count;
}

uint32_t hash_ip(uint32_t ip) {
    ip = ((ip >> 16) ^ ip) * 0x85ebca6b;
    ip = ((ip >> 13) ^ ip) * 0xc2b2ae35;
    ip = (ip >> 16) ^ ip;
    return ip;
}

void add_ip(uint32_t ip) {
    uint32_t hash = hash_ip(ip);
    int index = hash & (M - 1);
    int zeros = leading_zeros(hash, P);
    if (zeros > registers[index]) {
        registers[index] = zeros;
    }
}

double hyperloglog() {
    double sum = 0;
    int zero_count = 0;
    
    for (int i = 0; i < M; i++) {
        sum += 1.0 / (1 << registers[i]);
        if (registers[i] == 0) zero_count++;
    }
    
    double estimate = 0.7213 / (1 + 1.079 / M) * M * M / sum;
    
    if (estimate <= 2.5 * M) {
        if (zero_count > 0) {
            estimate = M * log((double)M / zero_count);
        }
    }
    
    return estimate;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    memset(registers, 0, sizeof(registers));
    
    char ip[20];
    int count = 0;
    
    while (fscanf(input, "%s", ip) != EOF) {
        add_ip(ip_to_int(ip));
        count++;
    }
    
    double unique_estimate = hyperloglog();
    fprintf(output, "%.0f\n", unique_estimate);
    
    fclose(input);
    fclose(output);
    return 0;
}