#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STD_BUFFER_SIZE 100

void Track_Search(FILE* file, const char* query) {

    char line[STD_BUFFER_SIZE] = "\0";
    int line_count = 0;

    while(fgets(line, STD_BUFFER_SIZE, file)) {

        line_count++;
        const char* match = strstr(line, query);

        if(!match) {
            continue;
        }
        // Track 13: Robbie Williams – Supreme
        printf("Track %d: %s", line_count, match);
    }
}

int main(int xargs, char* args[]) {

    char path[STD_BUFFER_SIZE];
    printf("Bitte Dateiname eingeben: ");
    scanf("%s", path);

    // Try opening the file
    FILE* file = fopen(path, "r");

    // If file open was unsuccessful, throw an error
    if (!file) {
        printf("Couldn't open file %s\n", path);
        return 1;
    }

    char query[STD_BUFFER_SIZE];
    printf("Bitte den Suchstring eingeben: ");
    scanf("%s", query);

    Track_Search(file, query);

    fclose(file);
    return 0;
}