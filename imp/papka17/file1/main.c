#include <stdio.h>
#define NDEBUG

int main() {
    printf("Compiler: ");
    
    #if defined(_MSC_VER)
        printf("MSVC\n");
    #elif defined(__clang__)
        printf("clang\n");
    #elif defined(__GNUC__) || defined(__GNUG__)
        printf("GCC\n");
    #elif defined(__TINYC__)
        printf("TCC\n");
    #else
        printf("unknown\n");
    #endif
    
    printf("Bitness: ");
    
    #if defined(_WIN64) || defined(__x86_64__) || defined(__LP64__)
        printf("64\n");
    #else
        printf("32\n");
    #endif
    
    printf("Asserts: ");
    
    #ifdef NDEBUG
        printf("disabled\n");
    #else
        printf("enabled\n");
    #endif
    
    return 0;
}