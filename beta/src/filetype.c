#include "filetype.h"
#include "error.h"
#include "typing.h"
#include "debug.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

FILE *fp = NULL;
int fp_pos = 0;

void close_file()
{
    if (fp != NULL)
        fclose(fp);
}

int open_file(char *filepath)
{
    fp = fopen(filepath, "r"); // returns heap memory location

    if (fp == NULL) {
        print_error(strerror(errno));
        return -1;
    }

    return 0;
}

void type_file_loop()
{
    int result = 0;
    char buffer[80];
    struct stats typing_stats = {0,0};

    do {
        result = get_target_line(buffer, BUFSIZE);
        type_target(buffer, &typing_stats);

        // delete last three lines
        printf("\r\033[K\033[A\033[K\033[A\033[K");

        fflush(stdin);
    } while (result != -1);

    // print out stats 
    type_target("\0", &typing_stats);
}

int get_target_line(char *buffer, size_t size)
{   // algorithm
    // iterate thru file byte by byte
    // When ever there's a space, consider that a word
    // Read until you've fit the max words in the buffer
    // remember that you need to add \0 at the end
    // \n gets changed to ' ', unless it's at the very end, then \0

    int c;
    int bufpos = 0;
    int isspace = 0;
    int hasbegun = 0;
    int wep = 0; // Word End Position
    char *org = buffer;

    memset(buffer, '\0', size);

    if (fp == NULL) {
        return -1;
    }

    fp_pos = ftell(fp);
    
    while (1) {
        if (bufpos == size - 1) {
            if (wep > 0) {
                memset(org + wep, '\0', size - wep);
                fseek(fp, fp_pos, SEEK_SET);
            }
            DEBUG_PRINT("%d - %d\n", fp_pos, wep);
            break;
        }

        c = fgetc(fp);

        switch (c) {
        case EOF:
            return -1;
        case '\t':
        case '\n':
        case '\0':
        case ' ':
           if (!isspace && hasbegun) {
                isspace = 1;
                wep = bufpos;   // position in buffer of word that fits (end of word)
                ++bufpos;
                fp_pos = ftell(fp);
            }
            break;
        default:
            if (isspace) {
                *buffer++ = ' ';

                fp_pos = ftell(fp) - 1; // position in file of word that won't fit
            }

            *buffer++ = c;
            ++bufpos;

            hasbegun = 1;
            isspace = 0;

            break;
        }
    }

    return 0;
}

