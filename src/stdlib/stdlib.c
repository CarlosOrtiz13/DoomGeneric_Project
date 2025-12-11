#include "stdlib.h"
#include "../memory/heap/kheap.h"
#include <stddef.h>


void* malloc(size_t size)
{
    return kzalloc(size);
}

void free(void* ptr)
{
    kfree(ptr);
}

void* calloc(size_t nmemb, size_t size)
{
    size_t total = nmemb * size;
    void* ptr = kzalloc(total);
    return ptr;
}

void* realloc(void* ptr, size_t size)
{
    if (!ptr) return kzalloc(size);
    if (size == 0) { 
        kfree(ptr);
        return NULL;
    }
    
    void* new_ptr = kzalloc(size);
    if (!new_ptr) return NULL;
    
    char* src = (char*)ptr;
    char* dst = (char*)new_ptr;
    for (size_t i = 0; i < size; i++) {
        dst[i] = src[i];
    }
    
    kfree(ptr);
    return new_ptr;
}

int atoi(const char* str)
{
    int result = 0;
    int sign = 1;
    
    while (*str == ' ') str++;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') str++;
    
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}

int abs(int n)
{
    return n < 0 ? -n : n;
}

// Very simple sscanf - only handles %x (hex) format for Doom's needs
int sscanf(const char* str, const char* format, ...)
{
    // For now, just a stub that handles %x
    if (format[0] == '%' && format[1] == 'x')
    {
        unsigned int* result = __builtin_va_arg(*(va_list*)&format + 1, unsigned int*);
        // Simple hex parser
        unsigned int val = 0;
        while (*str == ' ' || *str == '\t') str++;
        while (*str)
        {
            if (*str >= '0' && *str <= '9')
                val = val * 16 + (*str - '0');
            else if (*str >= 'a' && *str <= 'f')
                val = val * 16 + (*str - 'a' + 10);
            else if (*str >= 'A' && *str <= 'F')
                val = val * 16 + (*str - 'A' + 10);
            else
                break;
            str++;
        }
        *result = val;
        return 1;
    }
    return 0;
}

// Simple atof - converts string to float
double atof(const char* str)
{
    double result = 0.0;
    double sign = 1.0;
    double decimal = 0.1;
    int seen_decimal = 0;
    
    while (*str == ' ' || *str == '\t') str++;
    
    if (*str == '-')
    {
        sign = -1.0;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }
    
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            if (seen_decimal)
            {
                result += (*str - '0') * decimal;
                decimal *= 0.1;
            }
            else
            {
                result = result * 10.0 + (*str - '0');
            }
        }
        else if (*str == '.' && !seen_decimal)
        {
            seen_decimal = 1;
        }
        else
        {
            break;
        }
        str++;
    }
    
    return result * sign;
}

long atol(const char* str)
{
    return (long)atoi(str);
}

int mkdir(const char* path, int mode)
{
    (void)path;
    (void)mode;
    return 0; // Stub - always succeed
}

int vsnprintf(char* buf, int buf_len, const char* s, va_list args)
{
    // Very simple implementation - just copy the format string
    // In a real implementation, you'd process format specifiers
    int i = 0;
    while (*s && i < buf_len - 1)
    {
        buf[i++] = *s++;
    }
    buf[i] = '\0';
    (void)args;
    return i;
}

unsigned int __rand_seed = 1;
