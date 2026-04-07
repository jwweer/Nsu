#include <stdio.h>

#define MOD_VAL 1000000007
#define MAX_DIM 300

int var_cnt;
int eq_cnt;
int modulus;
int matrix[MAX_DIM][MAX_DIM] = {0};
int constants[MAX_DIM] = {0};
int matrix_rank;

int fast_pow(int base, int exponent, int mod) {
    long long result = 1;
    long long current = base % mod;
    
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * current) % mod;
        }
        current = (current * current) % mod;
        exponent >>= 1;
    }
    
    return (int)result;
}

int find_inverse(int value, int mod) {
    return fast_pow(value, mod - 2, mod);
}

int eliminate() {
    int i, j;
    int current_row = 0;
    int current_col = 0;
    int pivot_row;
    
    while (current_row < eq_cnt && current_col < var_cnt) {
        pivot_row = -1;
        for (i = current_row; i < eq_cnt; i++) {
            if (matrix[i][current_col] != 0) {
                pivot_row = i;
                break;
            }
        }
        
        if (pivot_row == -1) {
            current_col++;
            continue;
        }
        
        if (pivot_row != current_row) {
            for (j = current_col; j < var_cnt; j++) {
                int temp_val = matrix[current_row][j];
                matrix[current_row][j] = matrix[pivot_row][j];
                matrix[pivot_row][j] = temp_val;
            }
            int temp_const = constants[current_row];
            constants[current_row] = constants[pivot_row];
            constants[pivot_row] = temp_const;
        }
        
        int inv_val = find_inverse(matrix[current_row][current_col], modulus);
        for (j = current_col; j < var_cnt; j++) {
            matrix[current_row][j] = (int)((long long)matrix[current_row][j] * inv_val % modulus);
        }
        constants[current_row] = (int)((long long)constants[current_row] * inv_val % modulus);
        
        for (i = 0; i < eq_cnt; i++) {
            if (i != current_row && matrix[i][current_col] != 0) {
                int factor = matrix[i][current_col];
                for (j = current_col; j < var_cnt; j++) {
                    matrix[i][j] = (matrix[i][j] - (int)((long long)factor * matrix[current_row][j] % modulus) + modulus) % modulus;
                }
                constants[i] = (constants[i] - (int)((long long)factor * constants[current_row] % modulus) + modulus) % modulus;
            }
        }
        
        current_row++;
        current_col++;
    }
    
    matrix_rank = current_row;
    
    for (i = matrix_rank; i < eq_cnt; i++) {
        int all_zero = 1;
        for (j = 0; j < var_cnt; j++) {
            if (matrix[i][j] != 0) {
                all_zero = 0;
                break;
            }
        }
        if (all_zero && constants[i] != 0) {
            return -1;
        }
    }
    
    return matrix_rank;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d", &var_cnt, &eq_cnt, &modulus);
    
    for (int i = 0; i < eq_cnt; i++) {
        for (int j = 0; j < var_cnt; j++) {
            scanf("%d", &matrix[i][j]);
        }
        scanf("%d", &constants[i]);
    }
    
    int status = eliminate();
    
    if (status == -1) {
        printf("0\n");
    } else if (matrix_rank == var_cnt) {
        int solution[MAX_DIM] = {0};
        
        for (int i = 0; i < var_cnt; i++) {
            for (int j = 0; j < eq_cnt; j++) {
                if (j < matrix_rank && matrix[j][i] == 1) {
                    solution[i] = constants[j];
                    break;
                }
            }
        }
        printf("1\n");
        for (int i = 0; i < var_cnt; i++) {
            printf("%d\n", solution[i]);
        }
    } else {
        int free_vars = var_cnt - matrix_rank;
        long long total = 1;
        
        for (int i = 0; i < free_vars; i++) {
            total = (total * modulus) % MOD_VAL;
        }
        
        printf("%lld\n", total);
    }
    return 0;
}