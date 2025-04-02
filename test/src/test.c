#include "test.h"
#include "../../src/filetype.h"
#include "../../src/common.h"
#include "../../src/debug.h"

#include <stdio.h>
#include <string.h>

const char *tf1_lines[] = {
    TEST1_LINE1,
    TEST1_LINE2,
    TEST1_LINE3
};

const char *tf2_lines[] = {
    TEST2_LINE1,
    TEST2_LINE2,
    TEST2_LINE3
};

int run_test(char *filepath, const char *lines[])
{
    if (open_file(filepath) < 0) {
        return 0;
    }

    char buffer[BUFSIZE];
    int result = 0, pos = 0;

    do {
        result = get_target_line(buffer, BUFSIZE);

        if (buffer[0] != '\0') {
            if (!strcmp(buffer, lines[pos++]) == 0) {
                DEBUG_PRINT("*%s*\n*%s*\n", buffer, lines[pos - 1]);
                printf("%s - line %d failed\n", filepath, pos);
                close_file();
                return 0;
            }
        }
    } while (result != -1);

    close_file();
    return 1;
}
