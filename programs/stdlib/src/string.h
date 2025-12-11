#ifndef PEACHOS_STRING_H
#define PEACHOS_STRING_H

#include <stdbool.h>
#include <stddef.h>

char tolower(char s1);
int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
int strnlen_terminator(const char* str, int max, char terminator);
int istrncmp(const char* s1, const char* s2, int n);
int strncmp(const char* str1, const char* str2, int n);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, int count);
bool isdigit(char c);
int tonumericdigit(char c);
char* strtok(char* str, const char* delimiters);

// Your existing functions...
char tolower(char s1);
int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
// ... etc

// Add these declarations:
int strcmp(const char* str1, const char* str2);
void* memcpy(void* dest, const void* src, int count);
void* memset(void* ptr, int value, int num);
int memcmp(const void* s1, const void* s2, int n);
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);
int strcasecmp(const char* s1, const char* s2);
int strncasecmp(const char* s1, const char* s2, int n);
char* strcat(char* dest, const char* src);

#endif