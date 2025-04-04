#ifndef TEST_H
#define TEST_H

/*
#define TEST1_LINE1 "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
#define TEST1_LINE2 "there tech show know goes but does they hold forever contain cottage on dye gras"
#define TEST1_LINE3 "s air fryer gold cash door dash function only to server but many goes to the sho"
#define TEST1_LINE4 "w after a lie from bridge deletion operation for many to go around for the time."

#define TEST2_LINE1 "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
#define TEST2_LINE2 "there tech show know goes but does they hold forever contain cottage on dye gras"
#define TEST2_LINE3 "s air fryer gold cash door dash function only to server but many goes to the sho"
#define TEST2_LINE4 "w after a lie from bridge deletion operation for many to go around for the time"
#define TEST2_LINE5 "and extra long time ago." 
*/

#define TEST1_LINE1 "there tech show know goes but does they hold forever contain cottage air fryer"
#define TEST1_LINE2 "golf cash door dash function only to server but many goes to the show after a"
#define TEST1_LINE3 "lie from bridge deletion operation for many to go around for the time."

#define TEST2_LINE1 "hello there old chap my boy. It was a pleasure having over last weekend and,"
#define TEST2_LINE2 "there could be another man who plays the part of the wolf in the play from,"
#define TEST2_LINE3 "therefore who was there this time dude."

#define TEST1_FILEPATH "../testfiles/testfile1"
#define TEST2_FILEPATH "../testfiles/testfile2"

extern const char *tf1_lines[];
extern const char *tf2_lines[];

int run_test(char *filepath, const char *lines[]);

#endif // TEST_H
