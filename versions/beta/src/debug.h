#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        do { fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)
#else
    #define DEBUG_PRINT(fmt, ...) \
        do {} while (0)
#endif

#endif // DEBUG_H
