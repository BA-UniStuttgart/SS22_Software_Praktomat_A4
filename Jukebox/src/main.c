#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Checks if the amount of arguments supplied is valid
int _check_args(int xargs) {
    // 1. Parameter is Path to the executable
    // 2. Parameter is Path to jukebox.txt
    // 3. Query Parameter
    // If less or too many arguments have been supplied, then throw an error
    if (xargs < 3) {
        printf("Not enough arguments supplied\n");
        return 1;
    } else if (xargs > 3) {
        printf("Too many arguments supplied\n");
        return 1;
    }

    return 0;
}

void Track_Search(FILE* file, char* query) {

    char line[100] = "\0";
    int line_count = 0;

    while(fgets(line, 100, file) != NULL) {

        line_count++;
        char* found = strstr(line, query);

        if(found == NULL) {
            continue;
        }
        // Track 13: Robbie Williams – Supreme
        printf("Track %d: %s", line_count, found);
    }
}

int main(int xargs, char* args[]) {
    
    if (_check_args(xargs)) {
        return 1;
    }

    char* jukebox_path = args[1];
    char* query = args[2];
    
    // Try opening the file
    FILE* jukebox_file = fopen(jukebox_path, "r");

    // If file open was unsuccessful, throw an error
    if (jukebox_file == NULL) {
        printf("Couldn't open file %s\n", jukebox_path);
        return 1;
    }

    Track_Search(jukebox_file, query);

    fclose(jukebox_file);
    return 0;
}