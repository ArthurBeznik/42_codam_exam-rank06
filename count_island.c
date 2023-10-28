#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFERSIZE 1024*1024

void dfs(char map[BUFFERSIZE], int size, int cols, int i, char count) {

	// check if we are still in the map and that the current element is 'X'
    if (!i || i < 0 || i > size || map[i] != 'X')
        return ;

	// replace current element with the appropriate value
    map[i] = count;

	// perform dfs on surrounding elements
    dfs(map, size, cols, i - cols, count); // previous row
    dfs(map, size, cols, i + cols, count); // following row
    dfs(map, size, cols, i - 1, count); // previous col
    dfs(map, size, cols, i + 1, count); // following col
}

bool get_size(char map[BUFFERSIZE], int *cols) {
    int same_len = 1;

	// loop over each char of the map
    for (int i = 0; map[i]; i++) {

		// if map contains invalid char
        if (!(map[i] == 'X' || map[i] == '.' || map[i] == '\n'))
            return false;
		
		// if newline
        if (map[i] == '\n') {

			// if cols is 0 set to same_len
            if(!(*cols))
                (*cols) = same_len;

			// if cols is diff than same_len (diff len lines)
            if(*(cols) != same_len)
                return false;

			// reset same_len
            same_len = 0;
        }
		// increment line len
        same_len++;
    }
    return true;
}

bool count_islands(char *file) {
    int fd;
    int size;
    int cols = 0;
    char map[BUFFERSIZE] = {0};
    
	// open file
    if ((fd = open(file, O_RDONLY)) == -1)
        return false;
	
	// read file + null-term
    if (!(size = read(fd, map, BUFFERSIZE)))
        return false;
    map[size] = '\0';

	// check if each line is the same len + set col size and has only valid char
    if (!(get_size(map, &cols)))
        return false;

	printf("cols = %d\n", cols);

	// start at '0' char
    char count = '0';

	// loop over char in the map until reach map size
    for (int i = 0; i < size; i++) {

		// if char to be replaced is found
        if (map[i] == 'X') {

			// perform dfs
            dfs(map, size, cols, i, count);

			// increment count to next value (1 - 2 - 3 - ...)
            count++;
        }
    }

	// display the new map
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
