#include <stdio.h>
#include <stdarg.h>

void test1(const char *fmt, ...);

#define TEST1(fmt, ...) test1(fmt, ##__VA_ARGS__)

#define TEST2(fmt, args...) test1(fmt, ##args)


int main(void)
{
  test1("dsc", 10, "hello", 'A');
  TEST1("csd", 'A', "hello", 10);
  TEST2("sdc", "hello", 10, 'A');
  return 0;
}

void test1(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char *str;
  char symbol;
  int value;
  while (*fmt)
  {
    switch (*fmt++)
    {
      case 's':
        str = va_arg(ap, char *);
        printf("%s\n", str);
        break;
      case 'd':
        value = va_arg(ap, int);
        printf("%d\n", value);
        break;
      case 'c':
        symbol = va_arg(ap, int);
        printf("%c\n", symbol);
        break;
    }
  }
}
