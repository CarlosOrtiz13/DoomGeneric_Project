#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "string.h"
#include "strings.h"

char tolower(char s1)
{
    if (s1 >= 65 && s1 <= 90)
    {
        s1 += 32;
    }
    return s1;
}

int strlen(const char* ptr)
{
    int i = 0;
    while(*ptr != 0)
    {
        i++;
        ptr += 1;
    }
    return i;
}

int strnlen(const char* ptr, int max)
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        if (ptr[i] == 0)
            break;
    }
    return i;
}

int strnlen_terminator(const char* str, int max, char terminator)
{
    int i = 0;
    for(i = 0; i < max; i++)
    {
        if (str[i] == '\0' || str[i] == terminator)
            break;
    }
    return i;
}

int istrncmp(const char* s1, const char* s2, int n)
{
    unsigned char u1, u2;
    while(n-- > 0)
    {
        u1 = (unsigned char)*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}

int strncmp(const char* str1, const char* str2, int n)
{
    unsigned char u1, u2;
    while(n-- > 0)
    {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}

int strcmp(const char* str1, const char* str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* strcpy(char* dest, const char* src)
{
    char* res = dest;
    while(*src != 0)
    {
        *dest = *src;
        src += 1;
        dest += 1;
    }
    *dest = 0x00;
    return res;
}

char* strncpy(char* dest, const char* src, int count)
{
    int i = 0;
    for (i = 0; i < count-1; i++)
    {
        if (src[i] == 0x00)
            break;
        dest[i] = src[i];
    }
    dest[i] = 0x00;
    return dest;
}

char* strcat(char* dest, const char* src)
{
    char* d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

char* strchr(const char* s, int c)
{
    while (*s) {
        if (*s == (char)c) return (char*)s;
        s++;
    }
    return NULL;
}

char* strrchr(const char* s, int c)
{
    const char* last = NULL;
    while (*s) {
        if (*s == (char)c) last = s;
        s++;
    }
    return (char*)last;
}

int strcasecmp(const char* s1, const char* s2)
{
    while (*s1 && (tolower(*s1) == tolower(*s2))) {
        s1++;
        s2++;
    }
    return tolower(*(unsigned char*)s1) - tolower(*(unsigned char*)s2);
}

int strncasecmp(const char* s1, const char* s2, size_t n)
{
    while (n > 0 && *s1 && (tolower(*s1) == tolower(*s2))) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return tolower(*(unsigned char*)s1) - tolower(*(unsigned char*)s2);
}

void* memcpy(void* dest, const void* src, int count)
{
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for (int i = 0; i < count; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* memset(void* ptr, int value, int num)
{
    unsigned char* p = (unsigned char*)ptr;
    for (int i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

int memcmp(const void* s1, const void* s2, int n)
{
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    
    for (int i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

void* memmove(void* dest, const void* src, int n)
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    
    if (d < s) {
        for (int i = 0; i < n; i++) d[i] = s[i];
    } else {
        for (int i = n - 1; i >= 0; i--) d[i] = s[i];
    }
    return dest;
}

bool isdigit(char c)
{
    return c >= 48 && c <= 57;
}

int tonumericdigit(char c)
{
    return c - 48;
}

void itoa(int value, char* buffer)
{
    int i = 0;
    int is_negative = 0;
    
    if (value == 0)
    {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }
    
    if (value < 0)
    {
        is_negative = 1;
        value = -value;
    }
    
    while (value != 0)
    {
        int digit = value % 10;
        buffer[i++] = '0' + digit;
        value /= 10;
    }
    
    if (is_negative)
        buffer[i++] = '-';
    
    buffer[i] = '\0';
    
    // reverse result
    int start = 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

void itoa_hex(uint32_t value, char* buffer)
{
    static const char* hex = "0123456789ABCDEF";
    buffer[0] = '0';
    buffer[1] = 'x';
    int index = 2;
    
    for (int shift = 28; shift >= 0; shift -= 4)
    {
        uint8_t nibble = (value >> shift) & 0xF;
        buffer[index++] = hex[nibble];
    }
    
    buffer[index] = '\0';
}