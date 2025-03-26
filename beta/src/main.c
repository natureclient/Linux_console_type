#include "filetype.h"
#include "typing.h"
#include "terminal.h"
#include "debug.h"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void exit_handler(int signum);
void type_random_loop();

int main(int argc, char* argv[])
{
    DEBUG_PRINT("DEBUG ENABLED\n");

    int opt;

    signal(SIGINT, exit_handler);
    set_terminal_raw();

    while ((opt = getopt(argc, argv, "f:"))  != -1 ) {
        switch(opt) {
        case 'f':
            if (open_file(optarg) < 0)
                break;
            type_file_loop();
            break;
        default:
            break;
        }
    }

    reset_terminal();

    return 0;
}

void exit_handler(int signum)
{
    DEBUG_PRINT("EXITING...\n");

    close_file();
    reset_terminal();
    exit(0);
}

