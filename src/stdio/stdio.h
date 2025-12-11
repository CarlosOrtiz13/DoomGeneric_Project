#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>
#include <stdarg.h>

typedef struct { int unused; } FILE;
#define EOF (-1)

int putchar(int c);
int printf(const char* fmt, ...);

// Stubs for file operations
static inline FILE* fopen(const char* f, const char* m) { return NULL; }
static inline int fclose(FILE* f) { return EOF; }
static inline size_t fread(void* p, size_t s, size_t n, FILE* f) { return 0; }
static inline size_t fwrite(const void* p, size_t s, size_t n, FILE* f) { return 0; }
static inline int fseek(FILE* f, long o, int w) { return -1; }
static inline long ftell(FILE* f) { return -1L; }
static inline int fprintf(FILE* f, const char* fmt, ...) { return 0; }
static inline int sprintf(char* str, const char* fmt, ...) { return 0; }
static inline int snprintf(char* str, size_t sz, const char* fmt, ...) { return 0; }

#endif