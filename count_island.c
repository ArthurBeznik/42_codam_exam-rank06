#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFERSIZE 1024*1024

static int arr[10];

// error check i and map
// replace current element with count
// dfs surrounding elements
void dfs(char map[BUFFERSIZE], int size, int cols, int i, char count) {
    if (!i || i < 0 || i > size || map[i] != 'X')
        return ;

    map[i] = count;
	// printf("%d\n", count - 48);
	arr[count - 48] += 1;

    dfs(map, size, cols, i - cols, count);
    dfs(map, size, cols, i + cols, count);
    dfs(map, size, cols, i - 1, count);
    dfs(map, size, cols, i + 1, count);
}

//	init same_len to 1
//	loop over map element
//		check if invalid char => return false
//		check if newline
//			check if cols is not set => set it to same_len
//			check if cols is diff than same_len => return false (one line has a diff len from the rest)
//			reset same_len to 0
//		increment same_len
//	return true
bool get_size(char map[BUFFERSIZE], int *cols) {
    int same_len = 1;

    for (int i = 0; map[i]; i++) {
        if (!(map[i] == 'X' || map[i] == '.' || map[i] == '\n'))
            return false;
		
        if (map[i] == '\n') {
            if (!(*cols))
                (*cols) = same_len;

            if (*(cols) != same_len)
                return false;

            same_len = 0;
        }
        same_len++;
    }
    return true;
}

//	init fd, size, cols (= 0) and map[BUFSIZE] = {0}
//	open file + error check
//	read map + error check
//	null-term map[size]
//	check if not get_size => return false
//	init count to '0' (starting char)
//	loop over map size
//		if map[i] is X
//			dfs
//			increment count
//	write map
//	return true
bool count_islands(char *file) {
    int fd;
    int size;
    int cols = 0;
    char map[BUFFERSIZE] = {0};
	bool replaced = false;
    
    if ((fd = open(file, O_RDONLY)) == -1)
        return false;
	
    if (!(size = read(fd, map, BUFFERSIZE)))
        return false;
    map[size] = '\0';

    if (!(get_size(map, &cols)))
        return false;

    char count = '0';
	int curr = 0;
	arr[count] = 0;
    for (int i = 0; i < size; i++) {
        if (map[i] == 'X') {
			replaced = true;
            dfs(map, size, cols, i, count);
            count++;
        }
    }

	printf("%d\n", arr[0]);
	printf("%d\n", arr[1]);
	printf("%d\n", arr[2]);
	printf("%d\n", arr[3]);
	printf("%d\n", arr[4]);
	printf("%d\n", arr[5]);
	printf("%d\n", arr[6]);
	printf("%d\n", arr[7]);

	int max = 0;
	int num = 0;
	for (int i = 0; i < 10; i++) {
		num = arr[i];
		max = num > max ? num : max;
	}

	printf("%d\n", max);

	if (!replaced)
		return false;

    write(1, map, size);
    return true;
}

int main(int argc , char *argv[]) {
	if (argc != 2 || !count_islands(argv[1]))
		write(1,"\n",1);
	return 0;
}

/*

Assignment name  : count_island
Expected files   : *.c, *.h
Allowed functions: open, close, read, write, malloc, free
--------------------------------------------------------------------------------
Write a program that takes a file that contains lines of equal length. Those
lines contain characters that are either '.' or 'X'. All those lines put
together form rectangles of '.' containing "islands" of 'X'.
The maximum size of a line is 1024 characters, including the terminating
newline.
A column if formed of the set of characters in the file that are separated from
the start of their respective lines by the same number of characters.
Two characters are said to be touching if they are contiguous and on the same
line, or on contiguous lines and on the same column.
An "island" of 'X' means a set of 'X' touching each other.
The program must walk though the file and display it after replacing all the
'X' by a number corresponding to the position their island appears in the file,
starting at the beginning of the file.
There can be only one result.
If the file is empty, or there is an error (Incoherent input, for example), or
no parameters are passed, the program must display a newline.
The file contains at most 10 islands.
You will find examples in the subject directory.
Examples:
$>cat toto
.................XXXXXXXX..........................................
....................XXXXXXXXX.......XXXXXXXX.......................
.................XXXXXXXX..............XXX...XXXXX.................
.....................XXXXXX.....X...XXXXXXXXXXX....................
................................X..................................
......XXXXXXXXXXXXX.............X..................................
..................X.............XXXXXXXXX..........................
..................X.........XXXXXXXXXXXX...........................
..................X................................................
XX.............................................................XXXX
XX..................XXXXXXXXXXXXX.................................X
...................................................................
.................................................................X.
.....................XXXXX.......................................XX
$>
$>./count_island toto
.................00000000..........................................
....................000000000.......11111111.......................
.................00000000..............111...11111.................
.....................000000.....2...11111111111....................
................................2..................................
......3333333333333.............2..................................
..................3.............222222222..........................
..................3.........222222222222...........................
..................3................................................
44.............................................................5555
44..................6666666666666.................................5
...................................................................
.................................................................7.
.....................88888.......................................77
$>
$>cat qui_est_la
...................................................................
...X........X.....XXXXX......XXXXXXX...XXXXXXXXXX..XXXXXXXXXX......
...XX......XX....XX...XX....XX.....XX.....XXXX.....XXXXXXXXXX......
...XXXX..XXXX...XX.....XX...XX.....XX......XX......XX..............
...XX.XXXX.XX...XX.....XX...XX.....XX......XX......XX..............
...XX...X..XX...XX.....XX...XXXXXXXX.......XX......XXXXX...........
...XX......XX...XXXXXXXXX...XXXX...........XX......XXXXX...........
...XX......XX..XX.......XX..XX.XX..........XX......XX..............
...XX......XX..XX.......XX..XX...X.........XX......XX..............
...XX......XX..XX.......XX..XX....X......XXXXXX....XXXXXXXXXX......
...XX......XX.XX.........XX.XX.....XX..XXXXXXXXXX..XXXXXXXXXX..X...
...................................................................
$>
$>./count_island qui_est_la
...................................................................
...0........0.....11111......2222222...3333333333..4444444444......
...00......00....11...11....22.....22.....3333.....4444444444......
...0000..0000...11.....11...22.....22......33......44..............
...00.0000.00...11.....11...22.....22......33......44..............
...00...0..00...11.....11...22222222.......33......44444...........
...00......00...111111111...2222...........33......44444...........
...00......00..11.......11..22.22..........33......44..............
...00......00..11.......11..22...5.........33......44..............
...00......00..11.......11..22....6......333333....4444444444......
...00......00.11.........11.22.....77..3333333333..4444444444..8...
...................................................................
$>
$>cat -e rien
$>./count_island rien | cat -e
$
$>

*/
