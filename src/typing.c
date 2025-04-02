#include "typing.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>

void type_target(char *target, struct stats *session)
{
    time_t start, end;
    int pos = 0, haserror = 0, prev = -1, incorrect = 0, wordcount = 0,
        should_start_timer = 1;
    char c;

    printf("Accuracy: \033[1m%d %\033[0m\n", session->accuracy);
    printf("WPM: \033[1m%d\033[0m\n", session->wpm);
    printf("%s\r", target);
    fflush(stdout);

    if (target[0] == '\0')
        return;
    
    time(&start);

    while (target[pos] != '\0' && read(STDIN_FILENO, &c, 1) == 1) {
        if (should_start_timer) {
            time(&start);
            --should_start_timer;
        }

        // user entered correct key
        if (c == target[pos]) {
            ++pos;

            // if a space is encountered then a word has just finished
            if (c == ' ')
                ++wordcount;

            // if there was an error then use red color
            if (haserror) {
                if (c == ' ')
                    printf("\033[1;38;5;1m_\033[0m");
                else
                    printf("\033[1;38;5;1m%c\033[0m", c);
                ++incorrect;
            }
            else
                printf("\033[1;38;5;7m%c\033[0m", c);

            haserror = 0;
            fflush(stdout);
        }
        else {
            // check if user made a typing mistake
            // TODO make this more clear
            if (pos > prev) {
                haserror = 1;
                prev = pos;
            }
        } 
    }

    time(&end);
    double speed = difftime(end, start);
    
    session->accuracy = ((pos - incorrect) * 100) / pos;
    session->wpm = ((++wordcount) * 60) / (int)speed;
}
