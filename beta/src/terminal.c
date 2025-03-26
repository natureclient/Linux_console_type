#include "terminal.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

struct termios original;

void set_terminal_raw()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &original);

    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_iflag &= ~(ICRNL | IXON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);    
}

void reset_terminal()
{
    printf("\r\033[K"); // erase current line and move cursor to start
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

