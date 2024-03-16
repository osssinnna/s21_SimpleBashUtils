#include <getopt.h>  
#include <stdio.h>
#include <stdlib.h>

typedef struct {  //структура с опциями
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blanck", 0, 0, 's'},
                                       {
                                           0,
                                           0,
                                           0,
                                           0,
                                       }};

                                       
void parse_flags(int argc, char **argv, opt *options);
void print_file(FILE *f, opt *options);