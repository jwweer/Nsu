#include "pack.h"
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

int pack(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_bytes = 0;
    const char* fmt_ptr = format;
    
    while (*fmt_ptr) {
        switch (*fmt_ptr) {
            case '%': {
                fmt_ptr++;
                switch (*fmt_ptr) {
                    case 'd': {
                        int val = va_arg(args, int);
                        if (buffer) {
                            *(int*)(buffer + total_bytes) = val;
                        }
                        total_bytes += sizeof(int);
                        break;
                    }
                    case 'l': {
                        fmt_ptr++;
                        if (*fmt_ptr == 'f') {
                            double val = va_arg(args, double);
                            if (buffer) {
                                *(double*)(buffer + total_bytes) = val;
                            }
                            total_bytes += sizeof(double);
                        }
                        break;
                    }
                    case 's': {
                        char* str = va_arg(args, char*);
                        int len = strlen(str) + 1;
                        if (buffer) {
                            strcpy(buffer + total_bytes, str);
                        }
                        total_bytes += len;
                        break;
                    }
                }
                break;
            }
            default:
                fmt_ptr++;
                break;
        }
        fmt_ptr++;
    }
    
    va_end(args);
    return total_bytes;
}