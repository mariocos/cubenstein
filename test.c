#include <stdlib.h>
#include <stdio.h>

int	get_hex(char **strs)
{
	unsigned int	ret;

	ret = 0;
	ret += atoi(strs[0]);
	ret += atoi(strs[1]) * 16^2;
	ret += atoi(strs[2]) * 16^4;
	printf("ret is %d and in hex [%x]\n", ret);
	return (ret);
}


int main(void)
{
	char **str;
}