#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL
} JsonType;

typedef struct JsonValue {
    JsonType type;
    union {
        struct {
            char **keys;
            struct JsonValue **values;
            int count;
        } object;
        struct {
            struct JsonValue **items;
            int count;
        } array;
        char *string;
        char *number;
        int boolean;
    };
} JsonValue;

void skip_spaces(char **s) {
    while (**s && isspace((unsigned char)**s)) (*s)++;
}

char *parse_string(char **s) {
    skip_spaces(s);
    if (**s != '"') return NULL;
    (*s)++;
    char *start = *s;
    while (**s && **s != '"') (*s)++;
    int len = *s - start;
    char *str = malloc(len + 1);
    memcpy(str, start, len);
    str[len] = '\0';
    if (**s == '"') (*s)++;
    return str;
}

JsonValue *parse_value(char **s);

JsonValue *parse_object(char **s) {
    skip_spaces(s);
    if (**s != '{') return NULL;
    (*s)++;
    
    JsonValue *val = malloc(sizeof(JsonValue));
    val->type = JSON_OBJECT;
    val->object.keys = NULL;
    val->object.values = NULL;
    val->object.count = 0;
    
    skip_spaces(s);
    if (**s == '}') {
        (*s)++;
        return val;
    }
    
    while (1) {
        skip_spaces(s);
        char *key = parse_string(s);
        if (!key) break;
        
        skip_spaces(s);
        if (**s != ':') {
            free(key);
            break;
        }
        (*s)++;
        
        JsonValue *value = parse_value(s);
        if (!value) {
            free(key);
            break;
        }
        
        val->object.count++;
        val->object.keys = realloc(val->object.keys, val->object.count * sizeof(char*));
        val->object.values = realloc(val->object.values, val->object.count * sizeof(JsonValue*));
        val->object.keys[val->object.count - 1] = key;
        val->object.values[val->object.count - 1] = value;
        
        skip_spaces(s);
        if (**s == '}') {
            (*s)++;
            break;
        }
        if (**s == ',') {
            (*s)++;
        }
    }
    
    return val;
}

JsonValue *parse_array(char **s) {
    skip_spaces(s);
    if (**s != '[') return NULL;
    (*s)++;
    
    JsonValue *val = malloc(sizeof(JsonValue));
    val->type = JSON_ARRAY;
    val->array.items = NULL;
    val->array.count = 0;
    
    skip_spaces(s);
    if (**s == ']') {
        (*s)++;
        return val;
    }
    
    while (1) {
        skip_spaces(s);
        JsonValue *item = parse_value(s);
        if (!item) break;
        
        val->array.count++;
        val->array.items = realloc(val->array.items, val->array.count * sizeof(JsonValue*));
        val->array.items[val->array.count - 1] = item;
        
        skip_spaces(s);
        if (**s == ']') {
            (*s)++;
            break;
        }
        if (**s == ',') {
            (*s)++;
        }
    }
    
    return val;
}

JsonValue *parse_number(char **s) {
    JsonValue *val = malloc(sizeof(JsonValue));
    val->type = JSON_NUMBER;
    char *start = *s;
    if (**s == '-') (*s)++;
    while (isdigit((unsigned char)**s)) (*s)++;
    int len = *s - start;
    val->number = malloc(len + 1);
    memcpy(val->number, start, len);
    val->number[len] = '\0';
    return val;
}

JsonValue *parse_value(char **s) {
    skip_spaces(s);
    if (!**s) return NULL;
    
    if (**s == '{') return parse_object(s);
    if (**s == '[') return parse_array(s);
    if (**s == '"') {
        JsonValue *val = malloc(sizeof(JsonValue));
        val->type = JSON_STRING;
        val->string = parse_string(s);
        return val;
    }
    if (strncmp(*s, "true", 4) == 0 && !isalnum((*s)[4])) {
        JsonValue *val = malloc(sizeof(JsonValue));
        val->type = JSON_BOOLEAN;
        val->boolean = 1;
        *s += 4;
        return val;
    }
    if (strncmp(*s, "false", 5) == 0 && !isalnum((*s)[5])) {
        JsonValue *val = malloc(sizeof(JsonValue));
        val->type = JSON_BOOLEAN;
        val->boolean = 0;
        *s += 5;
        return val;
    }
    if (strncmp(*s, "null", 4) == 0 && !isalnum((*s)[4])) {
        JsonValue *val = malloc(sizeof(JsonValue));
        val->type = JSON_NULL;
        *s += 4;
        return val;
    }
    if (**s == '-' || isdigit((unsigned char)**s)) {
        return parse_number(s);
    }
    
    return NULL;
}

JsonValue *find_path(JsonValue *root, char **path, int k) {
    JsonValue *cur = root;
    
    for (int i = 0; i < k; i++) {
        if (!cur) return NULL;
        
        if (path[i][0] == '[') {
            if (cur->type != JSON_ARRAY) return NULL;
            int idx = atoi(path[i] + 1);
            if (idx < 0 || idx >= cur->array.count) return NULL;
            cur = cur->array.items[idx];
        } else {
            if (cur->type != JSON_OBJECT) return NULL;
            int found = -1;
            for (int j = 0; j < cur->object.count; j++) {
                if (strcmp(cur->object.keys[j], path[i]) == 0) {
                    found = j;
                    break;
                }
            }
            if (found == -1) return NULL;
            cur = cur->object.values[found];
        }
    }
    
    return cur;
}

void print_value(JsonValue *val) {
    if (!val) {
        printf("null\n");
        return;
    }
    
    switch (val->type) {
        case JSON_OBJECT:
            printf("<object>\n");
            break;
        case JSON_ARRAY:
            printf("<array>\n");
            break;
        case JSON_STRING:
            printf("%s\n", val->string);
            break;
        case JSON_NUMBER:
            printf("%s\n", val->number);
            break;
        case JSON_BOOLEAN:
            printf("%s\n", val->boolean ? "true" : "false");
            break;
        case JSON_NULL:
            printf("null\n");
            break;
    }
}

void free_json(JsonValue *val) {
    if (!val) return;
    
    switch (val->type) {
        case JSON_OBJECT:
            for (int i = 0; i < val->object.count; i++) {
                free(val->object.keys[i]);
                free_json(val->object.values[i]);
            }
            free(val->object.keys);
            free(val->object.values);
            break;
        case JSON_ARRAY:
            for (int i = 0; i < val->array.count; i++) {
                free_json(val->array.items[i]);
            }
            free(val->array.items);
            break;
        case JSON_STRING:
            free(val->string);
            break;
        case JSON_NUMBER:
            free(val->number);
            break;
        default:
            break;
    }
    free(val);
}

int main() {
    char buffer[2000000];
    int pos = 0;
    int c;
    
    while ((c = getchar()) != EOF) {
        buffer[pos++] = c;
    }
    buffer[pos] = '\0';
    
    char *ptr = buffer;
    JsonValue *root = parse_value(&ptr);
    
    int k;
    while (scanf("%d", &k) == 1 && k != -1) {
        char **path = malloc(k * sizeof(char*));
        for (int i = 0; i < k; i++) {
            char buf[1000];
            scanf("%s", buf);
            path[i] = strdup(buf);
        }
        
        JsonValue *found = find_path(root, path, k);
        print_value(found);
        
        for (int i = 0; i < k; i++) free(path[i]);
        free(path);
    }
    
    free_json(root);
    
    return 0;
}