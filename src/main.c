#include "filetype.h"
#include "typing.h"
#include "terminal.h"
#include "debug.h"
#include "options.h"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void exit_handler(int signum);
void type_random_loop();
void print_help();

int main(int argc, char* argv[])
{
    DEBUG_PRINT("DEBUG ENABLED\n");

    int opt;

    signal(SIGINT, exit_handler);
    set_terminal_raw();

    while ((opt = getopt(argc, argv, "f:h"))  != -1 ) {
        switch(opt) {
        case HELP:
            print_help();
            break;
        case TEXT_FILE:
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

void print_help()
{
    printf("HELP\n");
    fflush(stdout);
}

