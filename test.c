#include <stdlib.h>
#include <stdio.h>
#include "srcs/cube.h"

#include <stdio.h>
#include <stdlib.h>

int get_hex(char **strs)
{
    unsigned int ret = 0;

	ret += atoi(strs[0]) << 16;//Red
	ret += atoi(strs[1]) << 8;//Green
	ret += atoi(strs[2]);//Blue
	return ret;
}

int main(void)
{
    char *str[] = {"255", "255", "255", NULL}; // Correct way to declare a string array

    int test;

    test = get_hex(str);

    printf("Hex value: %X\n", test);

    return 0;
}