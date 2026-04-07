#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef NO_MAIN
void DoAll(void);
#else
#define DoAll main
#endif

int DoAll(void) {
    FILE* fin;
    FILE* fout;
    
    #ifdef BINARY_IO
    fin = fopen("input.txt", "rb");
    fout = fopen("output.txt", "wb");
    #else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    #endif
    
    int N;
    #ifdef BINARY_IO
    fread(&N, sizeof(int), 1, fin);
    #else
    fscanf(fin, "%d", &N);
    #endif
    
    uint32_t* arr = (uint32_t*)malloc(N * sizeof(uint32_t));
    
    #ifdef BINARY_IO
    fread(arr, sizeof(uint32_t), N, fin);
    #else
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%u", &arr[i]);
    }
    #endif
    
    int max_len = 2;
    int best_start = 0;
    int best_diff = arr[1] - arr[0];
    
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            uint32_t diff = arr[j] - arr[i];
            int len = 2;
            uint32_t next = arr[j] + diff;
            
            for (int k = j + 1; k < N; k++) {
                if (arr[k] == next) {
                    len++;
                    next += diff;
                }
            }
            
            if (len > max_len || (len == max_len && i < best_start)) {
                max_len = len;
                best_start = i;
                best_diff = diff;
            }
        }
    }
    
    #ifdef BINARY_IO
    fwrite(&max_len, sizeof(int), 1, fout);
    fwrite(&best_start, sizeof(int), 1, fout);
    int end = best_start + max_len;
    fwrite(&end, sizeof(int), 1, fout);
    
    uint32_t val = arr[best_start];
    for (int i = 0; i < max_len; i++) {
        fwrite(&val, sizeof(uint32_t), 1, fout);
        val += best_diff;
    }
    #else
    fprintf(fout, "%d\n", max_len);
    fprintf(fout, "%d\n", best_start);
    fprintf(fout, "%d\n", best_start + max_len);
    
    uint32_t val = arr[best_start];
    for (int i = 0; i < max_len; i++) {
        fprintf(fout, "%u\n", val);
        val += best_diff;
    }
    #endif
    
    free(arr);
    fclose(fin);
    fclose(fout);
    
    return 0;
}