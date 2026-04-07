#include <stdint.h>

int64_t Sum(int l, int r);
int GetSize(void);

int Query(int l, int64_t sum) {
    int n = GetSize();
    int left = l;
    int right = n;
    int result = l;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int64_t current_sum = Sum(l, mid);
        
        if (current_sum <= sum) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}