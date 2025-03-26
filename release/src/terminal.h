#ifndef TERMINAL_H
#define TERMINAL_H

extern struct termios original; 

void set_terminal_raw();
void reset_terminal();

#endif // TERMINAL_H
