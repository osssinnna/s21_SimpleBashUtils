#include "s21_cat.h"

int main(int argc, char **argv) {
  opt options = {0};
  if (argc > 1) {
    parse_flags(argc, argv, &options);
    FILE *f = NULL;

    for (int i = 1; i < argc; ++i) {
      if (argv[i][0] != '-') {
        if ((f = fopen(argv[i], "r")) != NULL) {
          fseek(
              f, 0,
              SEEK_SET);  // для изменения файла устанавливаем начальную позицию
          print_file(f, &options);
          fclose(f);
        } else {
          printf("s21_cat: %s: No such file\n", argv[i]);
        }
      }
    }
  }
  return 0;
}

void parse_flags(int argc, char **argv, opt *options) {
  int option_index;  //создание переменной индекса опции
  int opt;           //создание переменной опции

  while ((opt = getopt_long(argc, argv, "+beEnstTv", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case '?':
        printf("usage: cat [-bens] [file ...]\n");
        exit(1);
    }
  }
  if (options->b) options->n = 0;
}
void print_file(FILE *f, opt *options) {
  int number = 0, new_line = 1;
  char pr_ch = 0, ch = 0;

  while ((ch = fgetc(f)) != EOF) {
    if (options->s) {
      if (pr_ch == '\n' && ch == '\n') {
        ch = fgetc(f);
        if (ch != '\n') {
          if (options->n) printf("%6d\t", ++number);
          options->e ? printf("$\n") : printf("\n");
        } else {
          continue;
        }
      }
      pr_ch = ch;
    }
    if (options->n) {
      if (new_line) {
        printf("%6d\t", ++number);
        new_line = 0;
      }
      if (ch == '\n') new_line = 1;
    }
    if (options->b) {
      if (new_line && ch != '\n') {
        printf("%6d\t", ++number);
        new_line = 0;
      }
      if (ch == '\n') new_line = 1;
    }
    if (options->e) {
      if (ch == '\n') printf("$");
    }
    if (options->t) {
      if (ch == '\t') {
        printf("^I");
        continue;
      }
    }
    if (options->v) {
      if (ch <= 31 && ch != 10 && ch != 9) {
        printf("^X");
        ch += 64;
      }
      if (ch == 127) {
        printf("^?");
        ch -= 64;
      }
    }
    printf("%c", ch);
  }
}
