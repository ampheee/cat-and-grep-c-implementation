#ifndef SRC_CAT_CAT_H_
#define SRC_CAT_CAT_H_

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


typedef struct opt{
    bool bFlag;
    bool eFlag;
    bool sFlag;
    bool tFlag;
    bool nFlag;
    bool vFlag;
} opts;

void Cat(int file_Desc, const char *name, opts options, int *count);

#endif  // SRC_CAT_CAT_H_
