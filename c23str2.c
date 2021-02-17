
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"


// Функция возвращает количество символов в файле
int get_len_str(char *name_file)
{
	FILE *f;
	f = fopen(name_file, "r");
	if (f == NULL)
		return (0);
	int len = 0;
	while(fgetc(f) != EOF)
		len++;
	fclose(f);
	return len;
}

// Открываем файл и закгружаем его в динамически выделенную память s
void	load_str(char *name_file, char *s)
{
	FILE *f;
	f = fopen(name_file, "r");
	if (f == NULL)
		return ;
	char ch;
	int i = 0;
	while((ch = fgetc(f)) != EOF)
	{
		s[i] = ch;
		i++;
	}	
	s[i] = '\0';
	fclose(f);
}


// 8. определение колличетва слов в строке.
int count_words(char *str)
{
	char prev = ' ';	
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isspace(str[i]) && !isspace(prev))
			count++;
		prev = str[i];
	}
	if (!isspace(prev))
		count++;
	return (count);
}

// Данная функция относится к 9 пункту
int is_polindrom(char *start, char *end)
{
	char *finish = end;
	while(start <= finish)
	{
		if (*start != *end)
			return (0);
		start++;
		end--;
	}
	return (1);
}

// 9. определение колличества симметричных слов в строке.
int SymmWords(char *str)
{
	int count = 0;
	char *start = str;
	char *end;
	
	while(*start != '\0')
	{
		if (!isspace(*start))
		{
			end = start;
			while(*end != '\0' && !isspace(*end))
				end++;
			count += is_polindrom(start, end - 1);
			start = end;
			continue ;
		}
		start++;
	}
	return (count);
}

int is_int_number(char *str)
{
	int i = 0;
	while (!isspace(str[i]) && str[i] != '\0')
	{
		if (!isdigit(str[i]))
		{
			if (str[i] == '.' && isdigit(str[i + 1]))
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

int is_real_number(char *str)
{
	int i = 0;
	while (!isspace(str[i]) && str[i] != '\0')
	{
		if (!isdigit(str[i]))
		{
			if (str[i] == '.' && isdigit(str[i + 1]))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int skip_digit(char *str)
{
	int i = 0;
	while(isdigit(str[i]) || str[i] == '.')
		i++;
	return (i);
}

// 10. Вычисление суммы целых чисел.
int SumWInt(char *str)
{
	int i = 0;
	int sum = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]))
		{
			if (is_real_number(str + i))
			{
				i += skip_digit(str + i);
				continue;
			}
			if (is_int_number(str + i) != 0)
			{
				int num = 0;
				sscanf(str + i, "%d", &num);
				sum += num;
				i += skip_digit(str + i);
				continue;
			}
		}
		i++;
	}
	return (sum);
}


// 11. Вычисление суммы вещественных чисел.
double SumWReal(char *str)
{
	int i = 0;
	double sum = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]))
		{
			if (is_real_number(str + i) != 0)
			{
				float num = 0.0;
				sscanf(str + i, "%f", &num);
				sum += num;
				i += skip_digit(str + i);
				continue;
			}
		}
		i++;
	}
	return (sum);
}

int main(void)
{
	char *name_file = "IN.TXT";
	
	int fl = 0;

	fl = get_len_str(name_file);
	char *s;

	s = malloc(fl + 1);
	if (s == NULL)
		return (-1);
	load_str(name_file, s);	
	printf("{%s}\n", s);
	
	FILE *f;
	f = fopen("RES.TXT", "w");
	if (f == NULL)
		return (-1);
	printf("9. SymmWords: %d\n", SymmWords(s));	
	printf("10. SumWInt: %d\n", SumWInt(s));	
	printf("11. SumWReal: %f\n", SumWReal(s));	
	fclose(f);
	free(s);
	return (0);
}
