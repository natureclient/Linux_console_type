#ifndef FILETYPE_H
#define FILETYPE_H

#include <stdio.h>

extern FILE *fp;
extern int fp_pos;

void close_file();
void type_file_loop();
int open_file(char *filepath);
int get_target_line(char *buffer, size_t size);

#endif // FILETYPE_H
