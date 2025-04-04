#ifndef TYPING_H
#define TYPING_H

#define MAX_BUFF_SIZE 60 // bytes

struct stats {
    int accuracy;
    int wpm;
};

void type_target(char *target, struct stats *session);

#endif // TYPING_H
