#include "main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

/**
*  _printf - entry point
* @format: string
* Return: length od string
*/

int _printf(const char *format, ...);
int _printf(const char *format, ...)
{
int charCount;
int errorStrLen;
char *errorStr;

va_list var_args;

charCount = 0;

if (format == NULL || format[0] == '\0')
return (-1);
va_start(var_args, format);

while (*format)
{
if (*format != '%')
{
write(1, format, 1);
charCount++;
}
else
{
format++;
if (*format == '\0')
break;

switch (*format)
{
case '%':
{
write(1, format, 1);
charCount++;
break;
}
case 'c':
{
_putchar(va_arg(var_args, int));
charCount++;
break;
}
case 's':
{
char *strArg = va_arg(var_args, char *);
if (strArg == NULL)
{
write(1, "(null)", 6);
charCount += 6;
}
else
{
int _strlength = 0;

while (strArg[_strlength] != '\0')
{
write(1, &strArg[_strlength], 1);
_strlength++;
}
charCount += _strlength;
}
break;
}
case 'd':
case 'i':
{
int intArg1 = va_arg(var_args, int);
int intStrLen2 = snprintf(NULL, 0, "%d", intArg1);
char *intStr1 = malloc(intStrLen2 + 1);
if (intStr1 == NULL)
{
va_end(var_args);
return (-1);
}
snprintf(intStr1, intStrLen2 + 1, "%d", intArg1);
write(1, intStr1, intStrLen2);
charCount += intStrLen2;
free(intStr1);
break;
}
default:
{
errorStrLen = snprintf(NULL, 0, "%%%c", *format);
errorStr = malloc(errorStrLen + 1);
if (errorStr == NULL)
{
va_end(var_args);
return (-1);
}
snprintf(errorStr, errorStrLen + 1, "%%%c", *format);
write(1, errorStr, errorStrLen);
charCount += errorStrLen;
free(errorStr);
break;
}
}
}
format++;
}

va_end(var_args);
return (charCount);
}
