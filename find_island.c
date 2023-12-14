#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFERSIZE 1024*1024

void dfs(char map[BUFFERSIZE], int size, int cols, int i, char count, int* islandSize) {
    // check if we are still in the map and that the current element is 'X'
    if (!i || i < 0 || i > size || map[i] != 'X')
        return;

    // replace current element with the appropriate value
    map[i] = count;
    (*islandSize)++;

    // perform dfs on surrounding elements
    dfs(map, size, cols, i - cols, count, islandSize); // previous row
    dfs(map, size, cols, i + cols, count, islandSize); // following row
    dfs(map, size, cols, i - 1, count, islandSize);     // previous col
    dfs(map, size, cols, i + 1, count, islandSize);     // following col
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
            if (!(*cols))
                (*cols) = same_len;

            // if cols is diff than same_len (diff len lines)
            if (*(cols) != same_len)
                return false;

            // reset same_len
            same_len = 0;
        }
        // increment line len
        same_len++;
    }
    return true;
}

void find_largest_island(char *file) {
    int fd;
    int size;
    int cols = 0;
    char map[BUFFERSIZE] = {0};

    // open file
    if ((fd = open(file, O_RDONLY)) == -1)
        return;

    // read file + null-term
    if (!(size = read(fd, map, BUFFERSIZE)))
        return;
    map[size] = '\0';

    // check if each line is the same len + set col size and has only valid char
    if (!(get_size(map, &cols)))
        return;

    printf("cols = %d\n", cols);

    // start at '0' char
    char count = '0';
    int maxIslandSize = 0;
    int currentIslandSize = 0;

    // loop over char in the map until reach map size
    for (int i = 0; i < size; i++) {
        // if char to be replaced is found
        if (map[i] == 'X') {
            // reset island size for the new island
            currentIslandSize = 0;

            // perform dfs
            dfs(map, size, cols, i, count, &currentIslandSize);

            // update the maximum island size if needed
            if (currentIslandSize > maxIslandSize) {
                maxIslandSize = currentIslandSize;
            }

            // increment count to next value (1 - 2 - 3 - ...)
            count++;
        }
    }

    // display the largest island
    write(1, map, size);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(1, "\n", 1);
        return 1;
    }

    find_largest_island(argv[1]);
    return 0;
}
