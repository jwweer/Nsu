#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUM 125000000 

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int n;
    fscanf(in, "%d", &n);
    
    int *nums = (int*)malloc(n * sizeof(int));
    int total = 0;
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &nums[i]);
        total += nums[i];
    }
    fclose(in);
    
    if (total % 2 != 0) {
        fprintf(out, "false\n");
        fclose(out);
        free(nums);
        return 0;
    }
    
    int target = total / 2;
    
    unsigned char *dp = (unsigned char*)calloc(target + 1, 1);
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = target; j >= nums[i]; j--) {
            if (dp[j - nums[i]]) {
                dp[j] = 1;
            }
        }
    }
    
    fprintf(out, "%s\n", dp[target] ? "true" : "false");
    
    free(dp);
    free(nums);
    fclose(out);
    return 0;
}