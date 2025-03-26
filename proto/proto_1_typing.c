#include <stdio.h>
#include <unistd.h>
#include <termios.h>

/*
    Author: Alex Zielinski

    Date: August 27, 2024

    This is a prototype for a Linux console typing practice program.
*/

struct stats {
    int total;
    int incorrect;
    float accuracy;
};

int main()
{
    struct termios raw, original;
    struct stats stat; 
    char c;
    char *target = "This is a test sentence for a prototype\0";
    int pos = 0, prev = -1;

    stat.total = 0;
    stat.incorrect = 0;
    stat.accuracy = 0.0f;

    // get terminal attributes and change to raw mode    
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_iflag &= ~(ICRNL | IXON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    printf("%s\n", target);

    // input loop
    while(target[pos] != '\0' && read(STDIN_FILENO, &c, 1) == 1)
    {
        if(c == target[pos])
        {
            ++stat.total;
            ++pos;
            printf("%c",c);

            // output buffer is flushed only when there's a newline
            // we need to  manually flush so
            fflush(stdout);
        }
        else
        {   if(pos > prev)
            {
                prev = pos;
                ++stat.incorrect;
            }
        }
    }

    stat.accuracy = ((float)(stat.total - stat.incorrect) / stat.total) * 100;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    printf("\nAccuracy: %.0f%\n", stat.accuracy);

    return 0;
}
