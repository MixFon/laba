#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

//Все возможные коды ошибок программы.
#define ERR_BAD_ARGS -1
#define ERR_MEMORY_ALLOCATION -2
#define ERR_OVERFLOW -3

int my_snprintf(char *buf, size_t num, const char *format, ...);
char *convert(unsigned long num, long base);

#endif
