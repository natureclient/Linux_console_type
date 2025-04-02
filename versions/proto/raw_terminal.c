#include <stdio.h>
#include <unistd.h>
#include <termios.h>

/*
    Author: Alex Zielinski

    Date: August 26, 2024

    This program reads key pressed from the keyboard and outputs the keys
    in the console on a new line. It's capable of detecting the Enter, Space
    and Backspace keys

    This is done by modifying the terminal settings via termios. The main
    flags we need to invert are:

        canonical mode (ICANON)
            makes input available line by line but we want it as
            soon as a key is pressed.
        echo (ECHO)
            prints everything that's pressed to screen. We'll use printf()
            to output key presses
        input processing and XON/XOFF flow controll (ICRNL, IXON)
            converting carriage returns to newlines. XON/XOFF is used for
            flow control in serial communicaiton. It can temporarily stop
            incoming data if the receiving device (terminal) is overwhelmed
            by data. In this case we want to ensure every key press goes
            straight to the terminal and isn't stopped
*/

int main()
{
    struct termios raw, original;
    char c;

    // get terminal attributes and change to raw mode    
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_iflag &= ~(ICRNL | IXON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    // input loop
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
    {
        if(c == '\r')
            printf("Enter");
        if(c == ' ')
            printf("Space");
        if(c == 0x7F)
            printf("Backspace\n");
        else
            printf("%c\n", c);
    }

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);

    return 0;
}
