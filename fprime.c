#include <stdio.h>

// Function to display prime factors of a number
void displayPrimeFactors(int n) {
    // Print the number itself
    printf("%d = ", n);

	if (n == 1) {
		printf("1");
		return ;
	}

	if (n == 2) {
		printf("2");
		return ;
	}

    // Check for 2 as a factor
    while (n % 2 == 0 && n > 2) {
        printf("2");
        n /= 2;
        if (n > 1) {
            printf(" * ");
        }
    }

    // Check for odd factors starting from 3
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0 && n > 2) {
            printf("%d", i);
            n /= i;
            if (n > 1) {
                printf(" * ");
            }
        }
    }

    // If the remaining number is greater than 1, it's a prime factor
    if (n > 1) {
        printf("%d", n);
    }

    printf("\n");
}

int main() {

    // Display prime factors of the number
	for (int i = 0; i < 1000; i++) {
		displayPrimeFactors(i);
	}

    return 0;
}
