#include <stdio.h>
#include <unistd.h>
#include <termios.h>

/*
    Author: Alex Zielinski

    Date: August 27, 2024

    This is a prototype for a Linux console typing practice program that makes
    use of cursor management via escape codes. 
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
    char *target = "ask took tone life appeared sweet beat loud skin simply rose light tone edge but softly answer month like call speak very\0";
    int pos = 0, prev = -1, error = 0;;

    stat.total = 0;
    stat.incorrect = 0;
    stat.accuracy = 0.0f;

    // get terminal attributes and change to raw mode    
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_iflag &= ~(ICRNL | IXON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    // print target phrase and move cursor to start
    printf("\e[38;5;8m%s\e[0G\e[0m", target);
    fflush(stdout);

    // input loop
    while(target[pos] != '\0' && read(STDIN_FILENO, &c, 1) == 1)
    {
        if(c == target[pos])
        {
            ++stat.total;
            ++pos;

            if(error)
                if(c == ' ')
                    printf("\e[1;38;5;1m_\e[0m");
                else
                    printf("\e[1;38;5;1m%c\e[0m", c);
            else
                printf("\e[1;38;5;7m%c\e[0m",c);

            error = 0;
            fflush(stdout);
        }
        else
        {   if(pos > prev)
            {
                error = 1;
                prev = pos;
                ++stat.incorrect;
            }
        }
    }

    stat.accuracy = ((float)(stat.total - stat.incorrect) / stat.total) * 100;

    // reset terminal options
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    printf("\nAccuracy: %.0f%\n", stat.accuracy);

    return 0;
}
