#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h> 

typedef struct State {
    char *regs[256];
} State;

State state;

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#define LOAD_LIB(lib) LoadLibrary(lib)
#define GET_FUNC(handle, name) GetProcAddress(handle, name)
#define LIB_EXT ".dll"
#else
#define EXPORT __attribute__((visibility("default")))
#define LOAD_LIB(lib) dlopen(lib, RTLD_LAZY)
#define GET_FUNC(handle, name) dlsym(handle, name)
#define LIB_EXT ".so"
#endif

void execute_command(char *line) {
    char *cmd = strtok(line, " \n");
    if (!cmd) return;
    
    char *colon = strchr(cmd, ':');
    char plugin[64], func[64];
    int argc = 0;
    char *args[4] = {NULL};
    
    if (colon) {
        int plen = colon - cmd;
        strncpy(plugin, cmd, plen);
        plugin[plen] = '\0';
        strcpy(func, colon + 1);
    } else {
        strcpy(plugin, "core");
        strcpy(func, cmd);
    }
    
    char *token;
    while ((token = strtok(NULL, " \n")) && argc < 3) {
        args[argc++] = token;
    }
    
    char libname[128];
    sprintf(libname, "%s%s", plugin, LIB_EXT);
    
    #ifdef _WIN32
    HINSTANCE lib = LoadLibrary(libname);
    #else
    void *lib = dlopen(libname, RTLD_LAZY);
    #endif
    
    if (!lib) {
        printf("Missing plugin %s\n", plugin);
        return;
    }
    
    char funcname[128];
    sprintf(funcname, "%s_%d", func, argc);
    
    #ifdef _WIN32
    void (*f)(State*, char*, char*, char*) = (void*)GetProcAddress(lib, funcname);
    #else
    void (*f)(State*, char*, char*, char*) = dlsym(lib, funcname);
    #endif
    
    if (!f) {
        printf("Missing function %s in plugin %s\n", funcname, plugin);
        #ifdef _WIN32
        FreeLibrary(lib);
        #else
        dlclose(lib);
        #endif
        return;
    }
    
    f(&state, args[0], args[1], args[2]);
}

int main() {
    char line[1005];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) > 0)
            execute_command(line);
    }
    return 0;
}