#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static int64_t* prefix_sum = NULL;
static int array_size = 0;

void Init(const int *arr, int n) {
    array_size = n;
    
    if (prefix_sum != NULL) {
        free(prefix_sum);
    }
    
    prefix_sum = (int64_t*)malloc((n + 1) * sizeof(int64_t));
    
    prefix_sum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + arr[i];
    }
}

int64_t Sum(int l, int r) {
    if (l < 0 || r > array_size || l > r) {
        return 0;
    }
    return prefix_sum[r] - prefix_sum[l];
}

int GetSize() {
    return array_size;
}