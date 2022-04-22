/*
 * Log.h
 *
 *  Created on: 2021Äê11ÔÂ25ÈÕ
 *      Author: MI
 */

#ifndef LOG_H_
#define LOG_H_


#include <iostream>

#define LOG_CONDITION intra_rank==0&&inter_rank==0

#define LOG_R0(fmt, ...)                \
    do {                                \
        if (LOG_CONDITION) {                \
            printf((fmt), __VA_ARGS__); \
            printf("\n");               \
        }                               \
    } while (0)

#define INFO_R0(fmt, ...)               \
    do {                                \
        if (LOG_CONDITION) {                \
            printf("[INFO] ");          \
            printf((fmt), __VA_ARGS__); \
            printf("\n");               \
        }                               \
    } while (0)

#define INFO(fmt, ...)              \
    do {                            \
        printf("[INFO] ");          \
        printf((fmt), __VA_ARGS__); \
        printf("\n");               \
    } while (0)

#define ERROR(fmt, ...)               \
    do {                              \
        printf("\033[0;31m[ERROR] "); \
        printf((fmt), __VA_ARGS__);   \
        printf("\n");                 \
        printf("\033[0;0m");          \
    } while (0)

// #define DEBUG(fmt, ...)
// #define DEBUG1(fmt)


#ifdef USE_DEBUG
#define DEBUG(fmt, args...)    \
    do {                       \
        printf("[DEBUG] ");    \
        printf((fmt), ##args); \
        printf("\n");          \
    } while (0)

#define DEBUG1(fmt)         \
    do {                    \
        printf("[DEBUG] "); \
        printf((fmt));      \
        printf("\n");       \
    } while (0)

#else
#define DEBUG(fmt, ...)
#define DEBUG1(fmt)
#endif


#endif /* LOG_H_ */
