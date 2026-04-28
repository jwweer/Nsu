#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

void write_int32(FILE *f, int32_t val) {
    fwrite(&val, 4, 1, f);
}

void write_int64(FILE *f, int64_t val) {
    fwrite(&val, 8, 1, f);
}

void write_double(FILE *f, double val) {
    fwrite(&val, 8, 1, f);
}

void write_cstring(FILE *f, const char *str) {
    fwrite(str, 1, strlen(str), f);
    fputc(0, f);
}

int write_bson_value(FILE *f, json_object *obj, const char *key);

int write_bson_document(FILE *f, json_object *obj) {
    long size_pos = ftell(f);
    write_int32(f, 0);
    
    json_object_object_foreach(obj, key, val) {
        write_bson_value(f, val, key);
    }
    fputc(0, f);
    
    long end_pos = ftell(f);
    int32_t size = end_pos - size_pos;
    fseek(f, size_pos, SEEK_SET);
    write_int32(f, size);
    fseek(f, end_pos, SEEK_SET);
    
    return size;
}

int write_bson_array(FILE *f, json_object *arr) {
    long size_pos = ftell(f);
    write_int32(f, 0);
    
    int len = json_object_array_length(arr);
    for (int i = 0; i < len; i++) {
        char idx[16];
        sprintf(idx, "%d", i);
        json_object *val = json_object_array_get_idx(arr, i);
        write_bson_value(f, val, idx);
    }
    fputc(0, f);
    
    long end_pos = ftell(f);
    int32_t size = end_pos - size_pos;
    fseek(f, size_pos, SEEK_SET);
    write_int32(f, size);
    fseek(f, end_pos, SEEK_SET);
    
    return size;
}

int write_bson_value(FILE *f, json_object *obj, const char *key) {
    int type = json_object_get_type(obj);
    
    switch (type) {
        case json_type_object:
            fputc(0x03, f);
            write_cstring(f, key);
            write_bson_document(f, obj);
            break;
            
        case json_type_array:
            fputc(0x04, f);
            write_cstring(f, key);
            write_bson_array(f, obj);
            break;
            
        case json_type_string:
            fputc(0x02, f);
            write_cstring(f, key);
            {
                const char *str = json_object_get_string(obj);
                int32_t len = strlen(str);
                write_int32(f, len + 1);
                fwrite(str, 1, len, f);
                fputc(0, f);
            }
            break;
            
        case json_type_int:
        case json_type_double:
            fputc(0x01, f);
            write_cstring(f, key);
            write_double(f, json_object_get_double(obj));
            break;
            
        case json_type_boolean:
            fputc(0x08, f);
            write_cstring(f, key);
            fputc(json_object_get_boolean(obj) ? 1 : 0, f);
            break;
            
        case json_type_null:
            fputc(0x0A, f);
            write_cstring(f, key);
            break;
            
        default:
            break;
    }
    
    return 0;
}

int main() {
    json_object *root = json_object_from_file("input.txt");
    if (!root) {
        return 1;
    }
    
    FILE *f = fopen("output.txt", "wb");
    if (!f) {
        json_object_put(root);
        return 1;
    }
    
    int type = json_object_get_type(root);
    
    if (type == json_type_object) {
        write_bson_document(f, root);
    } else if (type == json_type_array) {
        write_bson_array(f, root);
    }
    
    fclose(f);
    json_object_put(root);
    
    return 0;
}