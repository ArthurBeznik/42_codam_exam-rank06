/*

Write a program to check whether a given int is a multiplication of 3

*/

#include <stdlib.h>
#include <stdio.h>

int	mult_3(int num) {
	if (num % 3 == 0)
		return 0;
	return 1;
}

int	main(int argc, char **argv) {
	if (argc != 2)
		return 1;
	int	num = atoi(argv[1]);
	int	res = mult_3(num);
	if (res)
		printf("not mult of 3!\n");
	else
		printf("mult of 3!\n");
	return res;
}
