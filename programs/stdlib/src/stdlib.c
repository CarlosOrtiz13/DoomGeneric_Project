#include "stdlib.h"
#include "peachos.h"

void* calloc(size_t nmemb, size_t size)
{
    size_t total = nmemb * size;
    void* ptr = peachos_malloc(total);
    if (ptr) {
        // Need memset - make sure you have it
        char* p = (char*)ptr;
        for (size_t i = 0; i < total; i++) {
            p[i] = 0;
        }
    }
    return ptr;
}

void* realloc(void* ptr, size_t size)
{
    if (!ptr) return peachos_malloc(size);
    if (size == 0) { 
        peachos_free(ptr);
        return NULL;
    }
    
    // Allocate new block
    void* new_ptr = peachos_malloc(size);
    if (!new_ptr) return NULL;
    
    // Copy old data (simplified - we don't track old size)
    // This is inefficient but works for Doom
    char* src = (char*)ptr;
    char* dst = (char*)new_ptr;
    for (size_t i = 0; i < size; i++) {
        dst[i] = src[i];
    }
    
    peachos_free(ptr);
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

long atol(const char* str)
{
    return (long)atoi(str);
}

unsigned int __rand_seed = 1;

char* itoa(int i)
{
    static char text[12];
    int loc = 11;
    text[11] = 0;
    char neg = 1;
    if (i >= 0)
    {
        neg = 0;
        i = -i;
    }

    while(i)
    {
        text[--loc] = '0' - (i % 10);
        i /= 10;
    }

    if (loc == 11)
        text[--loc] = '0';
    
    if (neg)
        text[--loc] = '-';

    return &text[loc];
}

void* malloc(size_t size)
{
    return peachos_malloc(size);
}

void free(void* ptr)
{
    peachos_free(ptr);
}