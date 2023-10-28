/*

Implement a program that returns 1 if a number is a power of 2, 0 otherwise.

*/

#include <stdio.h>
#include <stdlib.h>

int power_of_2(int number) {
    // Check if the number is positive
    if (number <= 0) {
        return 0;
    }

    // A power of two in binary has only one '1' bit.
    // If the bitwise AND of the number and (number - 1) is 0,
    // then the number is a power of 2.
    return (number & (number - 1)) == 0;
}

int	main(void) {
	for (int n = 0; n < 102; n++) {
		int res = power_of_2(n);
		if (res)
			printf("%d is a power of 2\n", n);
		else
			printf("%d is not a power of 2\n", n);
	}

	int n0 = 1024;
	int res0 = power_of_2(n0);
		if (res0)
			printf("%d is a power of 2\n", n0);
		else
			printf("%d is not a power of 2\n", n0);

	int n1 = 1234;
	int res1 = power_of_2(n1);
		if (res1)
			printf("%d is a power of 2\n", n1);
		else
			printf("%d is not a power of 2\n", n1);

	return 0;
}