#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_


#include <stdio.h>
#include <unistd.h> 
#include <stdbool.h>
#include <regex.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#define buffSize 4096
#define errStr "Usage: ./grep [-ivclnhso] [-e pattern] [-f file] template [file ...]\n"
struct grep {
  size_t counter;
  char id[300][1000];
};
typedef struct opt{
    int eFlag;
    int iFlag;
    int vFlag;
    int cFlag;
    int lFlag;
    int nFlag;
    int hFlag;
    int sFlag;
    int fFlag;
    int oFlag;
    int l;
    int c;
    int n;
    int files;
}opts;

void handle_file(FILE* f, opts *options);
void get_pattern(const char* string);
void get_pattern_from_file(const char* name, char **argv);
void match_patterns(char* str, opts *options);
void print_By_Flags(opts options);
void grep(const char* name, opts *options, char **argv);
void parse_Opts(int argc, char **argv, opts *options);

#endif // SRC_GREP_GREP_H_
