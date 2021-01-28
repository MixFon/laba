#include "my_snprintf.h"
#include "stdio.h"
#include "string.h"

int main(void)
{
	char buf[100];
	size_t num = 20;
	int len = 0;
	char *str = "///%x///";
	//int digit = 2147483648;
	len = my_snprintf(buf, num, str, 214733483648);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);
	len = snprintf(buf, num, str, 214733483648);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);
	printf("\n");
	exit(0);
	
	str = "!!!!%d????";
	len = my_snprintf(buf, num, str, -2147483648);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%d????", 2147483647);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%d????%d>>>", 2147483647, 1234);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%c????%c>>>", 'a', 'x');
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%x????%x>>>", 15, 2147483647);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%o????%o>>>", 15, 2147483647);
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);

	len = my_snprintf(buf, num, "!!!!%s????%s>>>", "Hello", "world");
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);
	len = snprintf(buf, num, "!!!!%s????%s>>>", "Hello", "world");
	printf("%s   = [%d]\n", buf, len);
	memset(buf, 0, num);
	return (0);
}
// --------123-----6666----
