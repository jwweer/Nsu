#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_SIZE 1000000

unsigned int hash1(int x) {
    return ((unsigned int)x * 2654435761U) % BLOOM_SIZE;
}

unsigned int hash2(int x) {
    return ((unsigned int)x * 2246822519U) % BLOOM_SIZE;
}

unsigned int hash3(int x) {
    return ((unsigned int)x * 3266489917U) % BLOOM_SIZE;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    char *bloom = (char*)calloc(BLOOM_SIZE, sizeof(char));
    
    int result = 0;
    
    for (int i = 0; i <= n; i++) {
        int x;
        fscanf(input, "%d", &x);
        
        unsigned int h1 = hash1(x);
        unsigned int h2 = hash2(x);
        unsigned int h3 = hash3(x);
        
        if (bloom[h1] && bloom[h2] && bloom[h3]) {
            result = x;
            break;
        }
        
        bloom[h1] = 1;
        bloom[h2] = 1;
        bloom[h3] = 1;
    }
    
    fprintf(output, "%d\n", result);
    
    free(bloom);
    fclose(input);
    fclose(output);
    return 0;
}