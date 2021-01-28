#include "my_snprintf.h"

int my_snprintf(char *buf, size_t num, const char *format, ...)
{
    const char *runner;
    size_t count = 0;
    long int tmp_cd;
    unsigned int tmp_ox;
    char *outbuf;
    long i;

    if (buf == NULL && num != 0)
        return -1;
    va_list arg;
    va_start(arg, format);

    for (runner = format; *runner != '\0'; runner++)
    {
        while (*runner != '%')
        {
            if (count < num - 1)
            {
                *(buf + count) = *runner;
                count += 1;
            }
            else if (count == num - 1)
            {
                *(buf + count) = '\0';
                count += 1;
            }
            else
                count += 1;
            runner++;
			if (*runner == '\0')
				break;
        }
		if (*runner == '\0')
			break;
        runner++;
        switch (*runner)
        {
            case 'c':
                tmp_cd = va_arg(arg, int);
                if (count < num - 1)
                {
                    *(buf + count) = (char)tmp_cd;
                    count += 1;
                }
                else if (count == num - 1)
                {
                    *(buf + count) = '\0';
                    count += 1;
                }
                else
                    count += 1;
                break;
            case 'd':
                tmp_cd = va_arg(arg, int);
                if (tmp_cd < 0)
                {
                    tmp_cd = -tmp_cd;
                    if (count < num - 1)
                    {
                        *(buf + count) = '-';
                        count += 1;
                    }
                    else if (count == num - 1)
                    {
                        *(buf + count) = '\0';
                        count += 1;
                    }
                    else
                        count += 1;
                }
                outbuf = convert(tmp_cd, 10);
                for (i = 0; *(outbuf + i) != '\0'; i++)
                {
                    if (count < num - 1)
                    {
                        *(buf + count) = *(outbuf + i);
                        count += 1;
                    }
                    else if (count == num - 1)
                    {
                        *(buf + count) = '\0';
                        count += 1;
                    }
                    else
                        count += 1;
                }
                break;
            case 'o':
                tmp_ox = va_arg(arg, unsigned int);
                outbuf = convert(tmp_ox, 8);
                for (i = 0; *(outbuf + i) != '\0'; i++)
                {
                    if (count < num - 1)
                    {
                        *(buf + count) = *(outbuf + i);
                        count += 1;
                    }
                    else if (count == num - 1)
                    {
                        *(buf + count) = '\0';
                        count += 1;
                    }
                    else
                        count += 1;
                }
                break;
            case 'x':
                tmp_ox = va_arg(arg, unsigned int);
                outbuf = convert(tmp_ox, 16);
                for (i = 0; *(outbuf + i) != '\0'; i++)
                {
                    if (count < num - 1)
                    {
                        *(buf + count) = *(outbuf + i);
                        count += 1;
                    }
                    else if (count == num - 1)
                    {
                        *(buf + count) = '\0';
                        count += 1;
                    }
                    else
                        count += 1;
                }
                break;
            case 's':
                outbuf = va_arg(arg, char *);
                for (i = 0; *(outbuf + i) != '\0'; i++)
                {
                    if (count < num - 1)
                    {
                        *(buf + count) = *(outbuf + i);
                        count += 1;
                    }
                    else if (count == num - 1)
                    {
                        *(buf + count) = '\0';
                        count += 1;
                    }
                    else
                        count += 1;
                }
                break;
        }
    }
	//printf("Mark??\n");
    if (count <= num - 1)
        *(buf + count) = '\0';
    va_end(arg);
    return count;
}

char *convert(unsigned long num, long base)
{
    char all_nums[] = "0123456789abcdef";
    static char buf[50];
    char *ptr;

    ptr = &buf[49];
    *ptr = '\0';
    do
    {
        *--ptr = all_nums[num % base];
        num /= base;
    } while (num != 0);
    return (ptr);
}

