#include <stdio.h>

static char input_buffer[65536];
static int buffer_position = 0;
static int buffer_size = 0;

char next_char(FILE* file_pointer) {
    if (buffer_position == buffer_size) {
        buffer_size = fread(input_buffer, 1, 65536, file_pointer);
        buffer_position = 0;
        if (buffer_size == 0) return EOF;
    }
    return input_buffer[buffer_position++];
}

long long parse_integer(FILE* file_pointer) {
    long long result = 0;
    int negative_flag = 1;
    char symbol = next_char(file_pointer);
    
    while (symbol != EOF && (symbol < '0' || symbol > '9') && symbol != '-') 
        symbol = next_char(file_pointer);
    
    if (symbol == '-') {
        negative_flag = -1;
        symbol = next_char(file_pointer);
    }
    
    while (symbol >= '0' && symbol <= '9') {
        result = result * 10 + (symbol - '0');
        symbol = next_char(file_pointer);
    }
    
    return result * negative_flag;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    long long array_length = parse_integer(file);
    long long target_value = parse_integer(file);

    long long found_index = -1;
    for (long long position = 0; position < array_length; position++) {
        long long current_value = parse_integer(file);
        if (current_value == target_value) {
            found_index = position;
            break;
        }
        if (current_value > target_value) break;
    }

    if (found_index != -1) {
        printf("YES %lld\n", found_index);
    } else {
        printf("NO\n");
    }

    fclose(file);
    return 0;
}