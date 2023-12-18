#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int ref;  // Static variable to store the reference value

void ft_putnbr(int num) {
    char c;
    
    if (num >= 10)
        ft_putnbr(num / 10);
    c = num % 10 + '0';
    write(1, &c, 1);  // Recursive function to print a number character by character
}

void print_matrix(int max, int arr[max][max]) {
    int i, j;

    for (i = 0; i < max; i++) {
        for (j = 0; j < max; j++)
            printf("%i ", arr[i][j]);
        printf("\n");
    }
}

// set visited[r] to 1 (mark current node as visited)
// init int i
// for loop until max
//	if visited[i] = 0 && arr[r][i] = 1 (not visited yet and existing link)
//		compare ref and length + 1 and set ref accordingly
//		
void longest_path(int max, int arr[max][max], int visited[max], int r, int length) {
    visited[r] = 1;
    int i;

    for (i = 0; i < max; i++) {
        if (!visited[i] && arr[r][i]) {
            ref = (ref < length + 1) ? length + 1 : ref;  // Update the reference value
            longest_path(max, arr, visited, i, length + 1);  // Recursive call to explore the path
        }
    }

    visited[r] = 0;  // Reset the visited status for backtracking
}

// init i, j, arr[max][max], visited[max]
// for loop until max
//	zero fill arr[i][j] with 0
// for loop until max
//	fill visited[j] with 0
// while loop over *s
//	convert &s into i
//	convert &s into j
//	set arr[i][j] and arr[j][i] to 1 (mark links between nb)
// set ref to 2
// for loop until max
//	longest_path() max, arr, visited, i, 1
void solve_matrix(int max, char *s) {
    int i, j;
    int arr[max][max];
    int visited[max];

    for (i = 0; i < max; i++)
        visited[i] = 0;
        for (j = 0; j < max; j++)
            arr[i][j] = 0;

    while (*s) {
        i = ft_atoi(&s);
        j = ft_atoi(&s);
        arr[i][j] = 1;
        arr[j][i] = 1;
    }

    ref = 2;

    for (i = 0; i < max; i++)
        longest_path(max, arr, visited, i, 1);
}

bool ft_isdigit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

// while loop over **s
//	convert curr char (if is digit) to nb
//	increment *s
// if **s (= '-')
//	increment *s
// return num
int ft_atoi(char **s) {
    int num = 0;
    while (ft_isdigit(**s)) {
        num = num * 10 + **s - '0';
        (*s)++;
    }
    if (**s)
        (*s)++;
    return num;
}

// while loop over *s
//	convert str to nb
//	compare num and max and set max
// return max
int find_max(char *s) {
    int max = 0;
    int num = 0;

    while (*s) {
        num = ft_atoi(&s);
        max = num > max ? num : max;
    }
    return max;
}

// if argc is 2
//	store input in char *s
//	find max in s
//	solve matrix with max + 1 as size
//	put nb ref (longest chain)
// print newline
// return
int main(int argc, char **argv) {
    if (argc == 2) {
        char *s = argv[1];

        int max = find_max(s);
        solve_matrix(max + 1, s);
        ft_putnbr(ref);
    }
    write(1, "\n", 1);
    return 0;
}


/*

Assignment name  : g_diam
Expected files   : *.c, *.h
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a programe that takes a string. This string represents a graph and is
composed of series of links between this graph's nodes. Links are separated by
a single space. Nodes are represented by numbers, and links by two nodes
separated by a '-'. For exemple, if there is a link between nodes 2
and 3, it could be written as "2-3" or "3-2".

The program will display the number of nodes comprised in the longest chain,
followed by a '\n', given it's impossible to pass through a node more than once.

If the number of parameters is different from 1, the program displays a '\n'.

Examples:

$>./g_diam "17-5 5-8 8-2 2-8 2-8 17-21 21-2 5-2 2-6 6-14 6-12 12-19 19-14 14-42" | cat -e
10$
$>./g_diam "1-2 2-3 4-5 5-6 6-7 7-8 9-13 13-10 10-2 10-11 11-12 12-8 16-4 16-11 21-8 21-12 18-10 18-13 21-18" | cat -e
15$

*/
