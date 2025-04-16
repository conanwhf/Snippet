/*
 * XXXXXX Use to do what
 * iNova, conanwang, 08/2021
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include "XXXXXXX.h"

// for Log
#define ERROR_INFO 1
#define DEBUG_INFO 1
#if ERROR_INFO
#define err(fmt, args...) printf("[%s(%d)] err: " fmt, __FUNCTION__, __LINE__, ##args) /*debug function */
#else
#define err(fmt, args...)
#endif

#if DEBUG_INFO
#define dbg(fmt, args...) printf("[%s(%d)] dbg: " fmt, __FUNCTION__, __LINE__, ##args) /*debug function */
#else
#define dbg(fmt, args...)
#endif

int main()
{
    return 0;
}
