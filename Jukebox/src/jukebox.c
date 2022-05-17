#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STD_BUFFER_SIZE 100

/*
    Searches for a query string in a File

    @file File which will be searched
    @query The query string to be searched for
*/
void Track_Search(FILE* file, const char* query) {

    // Line buffer and line count
    char line[STD_BUFFER_SIZE] = "\0";
    int line_count = 0;

    // Read file line by line
    while(fgets(line, STD_BUFFER_SIZE, file)) {

        line_count++;

        // Check if line contains the query string
        const char* match = strstr(line, query);

        // If match was not found, skip.
        if(!match) {
            continue;
        }

        // Display match
        printf("Track %d: %s", line_count, match);
    }
}

int main() {

    // Set file path
    char path[STD_BUFFER_SIZE];
    printf("Bitte Dateiname eingeben: ");
    scanf("%s", path);

    // Try opening the file
    FILE* file = fopen(path, "r");

    // If file open was unsuccessful, throw an error and return
    if (!file) {
        printf("Couldn't open file %s\n", path);
        return 1;
    }

    // Set query
    char query[STD_BUFFER_SIZE];
    printf("Bitte den Suchstring eingeben: ");
    scanf("%s", query);

    // Search for query in file
    Track_Search(file, query);

    // Close file
    fclose(file);
    return 0;
}