#ifndef STRING_H
#define STRING_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// String functions
int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
int strnlen_terminator(const char* str, int max, char terminator);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, int count);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, int n);
int istrncmp(const char* s1, const char* s2, int n);
char* strcat(char* dest, const char* src);
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);
char* strdup(const char* str);

// Memory functions
void* memcpy(void* dest, const void* src, int count);
void* memset(void* ptr, int value, int num);
int memcmp(const void* s1, const void* s2, int n);
void* memmove(void* dest, const void* src, int n);

// Character functions (standard C signatures)
int tolower(int c);
int toupper(int c);
int isdigit(int c);
int isspace(int c);
int isalpha(int c);
int tonumericdigit(char c);

// Conversion functions
void itoa(int value, char* buffer);
void itoa_hex(uint32_t value, char* buffer);

// BSD string functions (also in strings.h)
int strcasecmp(const char* s1, const char* s2);
int strncasecmp(const char* s1, const char* s2, int n);

#endif