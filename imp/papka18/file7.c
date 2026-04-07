#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Value {
    int type; // 0: null, 1: bool, 2: number, 3: string, 4: object, 5: array
    union {
        int bool_val;
        double num_val;
        char* str_val;
        struct Object* obj_val;
        struct Array* arr_val;
    };
} Value;

typedef struct Object {
    char** keys;
    Value** values;
    int count;
    int capacity;
} Object;

typedef struct Array {
    Value** items;
    int count;
    int capacity;
} Array;

typedef struct Parser {
    char* json;
    int pos;
    int len;
} Parser;

void skip_whitespace(Parser* p) {
    while (p->pos < p->len && isspace(p->json[p->pos])) {
        p->pos++;
    }
}

char peek(Parser* p) {
    skip_whitespace(p);
    return p->pos < p->len ? p->json[p->pos] : 0;
}

char next(Parser* p) {
    skip_whitespace(p);
    return p->pos < p->len ? p->json[p->pos++] : 0;
}

Value* parse_value(Parser* p);

Value* parse_string(Parser* p) {
    if (next(p) != '"') return NULL;
    
    int start = p->pos;
    while (p->pos < p->len && p->json[p->pos] != '"') {
        p->pos++;
    }
    
    int len = p->pos - start;
    char* str = (char*)malloc(len + 1);
    strncpy(str, p->json + start, len);
    str[len] = 0;
    
    p->pos++; // Skip closing quote
    
    Value* val = (Value*)malloc(sizeof(Value));
    val->type = 3;
    val->str_val = str;
    return val;
}

Value* parse_number(Parser* p) {
    int start = p->pos;
    while (p->pos < p->len && (isdigit(p->json[p->pos]) || p->json[p->pos] == '.' || 
           p->json[p->pos] == 'e' || p->json[p->pos] == 'E' || p->json[p->pos] == '-' || 
           p->json[p->pos] == '+')) {
        p->pos++;
    }
    
    int len = p->pos - start;
    char* num_str = (char*)malloc(len + 1);
    strncpy(num_str, p->json + start, len);
    num_str[len] = 0;
    
    double num = strtod(num_str, NULL);
    free(num_str);
    
    Value* val = (Value*)malloc(sizeof(Value));
    val->type = 2;
    val->num_val = num;
    return val;
}

Value* parse_object(Parser* p) {
    if (next(p) != '{') return NULL;
    
    Object* obj = (Object*)malloc(sizeof(Object));
    obj->count = 0;
    obj->capacity = 8;
    obj->keys = (char**)malloc(obj->capacity * sizeof(char*));
    obj->values = (Value**)malloc(obj->capacity * sizeof(Value*));
    
    while (1) {
        char c = peek(p);
        if (c == '}') {
            p->pos++;
            break;
        }
        
        Value* key = parse_string(p);
        if (!key) break;
        
        if (next(p) != ':') break;
        
        Value* val = parse_value(p);
        
        obj->keys[obj->count] = key->str_val;
        obj->values[obj->count] = val;
        obj->count++;
        free(key);
        
        c = peek(p);
        if (c == ',') {
            p->pos++;
        } else if (c == '}') {
            continue;
        } else {
            break;
        }
    }
    
    Value* val = (Value*)malloc(sizeof(Value));
    val->type = 4;
    val->obj_val = obj;
    return val;
}

Value* parse_array(Parser* p) {
    if (next(p) != '[') return NULL;
    
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->count = 0;
    arr->capacity = 8;
    arr->items = (Value**)malloc(arr->capacity * sizeof(Value*));
    
    while (1) {
        char c = peek(p);
        if (c == ']') {
            p->pos++;
            break;
        }
        
        Value* item = parse_value(p);
        arr->items[arr->count++] = item;
        
        c = peek(p);
        if (c == ',') {
            p->pos++;
        } else if (c == ']') {
            continue;
        } else {
            break;
        }
    }
    
    Value* val = (Value*)malloc(sizeof(Value));
    val->type = 5;
    val->arr_val = arr;
    return val;
}

Value* parse_value(Parser* p) {
    char c = peek(p);
    if (c == '{') return parse_object(p);
    if (c == '[') return parse_array(p);
    if (c == '"') return parse_string(p);
    if (c == '-' || isdigit(c)) return parse_number(p);
    
    if (c == 't' || c == 'f') {
        if (strncmp(p->json + p->pos, "true", 4) == 0) {
            p->pos += 4;
            Value* val = (Value*)malloc(sizeof(Value));
            val->type = 1;
            val->bool_val = 1;
            return val;
        } else if (strncmp(p->json + p->pos, "false", 5) == 0) {
            p->pos += 5;
            Value* val = (Value*)malloc(sizeof(Value));
            val->type = 1;
            val->bool_val = 0;
            return val;
        }
    }
    
    if (c == 'n') {
        if (strncmp(p->json + p->pos, "null", 4) == 0) {
            p->pos += 4;
            Value* val = (Value*)malloc(sizeof(Value));
            val->type = 0;
            return val;
        }
    }
    
    return NULL;
}

void process_queries(Value* root) {
    int k;
    scanf("%d", &k);
    
    Value* current = root;
    
    for (int i = 0; i < k; i++) {
        char path[100];
        scanf("%s", path);
        
        if (current->type == 4) { // object
            for (int j = 0; j < current->obj_val->count; j++) {
                if (strcmp(current->obj_val->keys[j], path) == 0) {
                    current = current->obj_val->values[j];
                    break;
                }
            }
        } else if (current->type == 5) { // array
            int idx = atoi(path + 1); // Skip '['
            current = current->arr_val->items[idx];
        }
    }
    
    switch (current->type) {
        case 0: printf("null\n"); break;
        case 1: printf("%s\n", current->bool_val ? "true" : "false"); break;
        case 2: printf("%g\n", current->num_val); break;
        case 3: printf("\"%s\"\n", current->str_val); break;
        case 4: printf("<object>\n"); break;
        case 5: printf("<array>\n"); break;
    }
}

int main() {
    FILE* fin = fopen("input.txt", "r");
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    
    char* json = (char*)malloc(size + 1);
    fread(json, 1, size, fin);
    json[size] = 0;
    
    Parser parser;
    parser.json = json;
    parser.pos = 0;
    parser.len = size;
    
    Value* root = parse_value(&parser);
    
    char separator[10];
    while (fgets(separator, sizeof(separator), fin) && separator[0] != '<') {}
    
    int k;
    while (fscanf(fin, "%d", &k) == 1 && k != -1) {
        fseek(fin, 1, SEEK_CUR); // Skip newline
        
        Value* current = root;
        
        for (int i = 0; i < k; i++) {
            char path[100];
            fgets(path, sizeof(path), fin);
            path[strcspn(path, "\n")] = 0;
            
            if (current->type == 4) { // object
                for (int j = 0; j < current->obj_val->count; j++) {
                    if (strcmp(current->obj_val->keys[j], path) == 0) {
                        current = current->obj_val->values[j];
                        break;
                    }
                }
            } else if (current->type == 5) { // array
                int idx = atoi(path + 1);
                current = current->arr_val->items[idx];
            }
        }
        
        switch (current->type) {
            case 0: printf("null\n"); break;
            case 1: printf("%s\n", current->bool_val ? "true" : "false"); break;
            case 2: printf("%g\n", current->num_val); break;
            case 3: printf("\"%s\"\n", current->str_val); break;
            case 4: printf("<object>\n"); break;
            case 5: printf("<array>\n"); break;
        }
    }
    
    fclose(fin);
    free(json);
    
    return 0;
}