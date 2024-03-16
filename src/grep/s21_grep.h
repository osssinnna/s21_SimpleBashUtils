#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;      
  int i;      
  int v;      
  int c;      
  int l;      
  int n;      
  int h;      
  int o;     
  int s;     
  int f;      
  int grep_error;  
} Grep_opt;

typedef struct {
  char string[100][1000];
  int number;
} GrepString;

void GrepParse(int argc, char *argv[], Grep_opt *info, GrepString *pattern, GrepString *file);
void Grep_optI(Grep_opt *info, GrepString *pattern, int *reti, char *search_string, int i);
void GrepPerform(FILE *ptr, Grep_opt *info, GrepString *pattern, GrepString *file, int numb);
