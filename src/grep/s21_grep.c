#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int numb = 0;
  Grep_opt opt = {0};
  GrepString pattern = {0};
  GrepString file = {0};

  if (argc > 1) {
    GrepParse(argc, &*argv, &opt, &pattern, &file);
    for (int i = 0; i < (file.number); i++) {
      FILE *ptr;
      ptr = fopen(file.string[i], "r");
      if (NULL == ptr) {
        if (opt.s == 0) {
          printf("grep: %s: No such file or directory\n", file.string[i]);
        }
      } else {
        numb = i;
        GrepPerform(ptr, &opt, &pattern, &file, numb);
        fclose(ptr);
      }
    }
  }
  return 0;
}

void GrepParse(int argc, char *argv[], Grep_opt *opt, GrepString *pattern,
               GrepString *file) {
  int num = 0;
  while (((num = getopt_long(argc, argv, "e:ivclnhosf", 0, 0)) != -1)) {
    switch (num) {
      case 'e':
        opt->e = 1;
        memset(pattern->string[pattern->number], 0, 1000);
        strcpy(pattern->string[pattern->number++], optarg);
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'o':
        opt->o = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'f':
        opt->f = 1;
        FILE *pt;
        pt = fopen(argv[optind], "r");
        if (NULL == pt) {
          if (opt->s == 0) {
            printf("grep: %s: No such file or directory", argv[optind]);
          }
          opt->grep_error = 1;
        } else {
          while (!feof(pt)) {
            char string[1000] = {0};
            fscanf(pt, "%s", string);
            if (strcmp(pattern->string[pattern->number - 1], string) != 0) {
              memset(pattern->string[pattern->number], 0, 1000);
              strcpy(pattern->string[pattern->number++], string);
            }
          }
        }
        fclose(pt);
        optind++;
        break;
      default:
        opt->grep_error = 1;
        break;
    }
  }

  if (opt->e == 0 && opt->f == 0) {
    memset(pattern->string[pattern->number], 0, 1000);
    strcpy(pattern->string[pattern->number++], argv[optind]);
    optind++;
  }

  while (optind < argc) {
    memset(file->string[file->number], 0, 1000);
    strcpy(file->string[file->number++], argv[optind]);
    optind++;
  }
}

void Grep_optI(Grep_opt *opt, GrepString *pattern, int *reti,
               char *search_string, int i) {
  regex_t regex;
  if (opt->i == 1) {
    *reti = regcomp(&regex, pattern->string[i], REG_ICASE);
    *reti = regexec(&regex, search_string, 0, NULL, 0);
  } else {
    *reti = regcomp(&regex, pattern->string[i], 0);
    *reti = regexec(&regex, search_string, 0, NULL, 0);
  }
  regfree(&regex);
}

void GrepPerform(FILE *ptr, Grep_opt *opt, GrepString *pattern,
                 GrepString *file, int numb) {
  int reti;
  int reti2;
  int flag = 1;
  char search_string[4059];
  int counter = 0;
  int schet = 1;
  int new_file = 0;

  if (opt->grep_error == 0) {
    while (fgets(search_string, 4059, ptr) != NULL) {
      int global = 0;
      int flag_e = 0;
      int pred_schet = 0;
      int pred_file = 0;
      for (int i = 0; i < (pattern->number); i++) {
        Grep_optI(opt, pattern, &reti, search_string, i);

        if (opt->v == 1) {
          if (reti != 0) {
            flag = 1;

            if (opt->c == 1 && flag_e == 0) {
              counter++;
              flag_e = 1;
            };

            if (opt->l == 1) {
              new_file = 1;
            }
          } else {
            flag = 0;
            global = 1;
          }
        } else {
          if (reti == 0) {
            flag = 1;
            flag_e = 1;
            if (opt->c == 1 && opt->l == 0) {
              flag = 0;
              counter++;
            } else if (opt->c == 1 && opt->l == 1) {
              flag = 0;
              counter = 1;
            }
          } else if (reti != 0 && flag_e != 1) {
            flag = 0;
          }
        }

        if (opt->l == 1 && opt->v == 0) {
          if (reti == 0) {
            new_file = 1;
          }
          flag = 0;
        } else if (opt->l == 1 && opt->v == 1) {
          if (reti != 0) {
            new_file = 1;
          }
          flag = 0;
        } else if (opt->o == 1 && opt->v == 1 && opt->c == 0 && opt->l == 0) {
          if (reti != 0) {
            char *istr;
            char nach[1000];
            for (long unsigned int i = 0; i < strlen(search_string); i++) {
              nach[i] = search_string[i];
            }
            istr = strtok(nach, " ");
            while (istr != NULL) {
              int reti2;
              Grep_optI(opt, pattern, &reti2, istr, i);
              if (reti2 == 0) {
                if ((opt->h == 0 && (file->number) > 1)) {
                  printf("%s:", file->string[numb]);
                }
                if (opt->n == 1) {
                  printf("%d:", schet);
                }

                printf("%s\n", search_string);
              }
              istr = strtok(NULL, " ");
            }
          }
        } else if (opt->o == 1 && opt->v == 0 && opt->c == 0 && opt->l == 0) {
          if (reti == 0) {
            char *istr;
            istr = strtok(search_string, " ");
            while (istr != NULL) {
              Grep_optI(opt, pattern, &reti2, istr, i);

              if (reti2 == 0) {
                if ((opt->h == 0 && (file->number) > 1)) {
                  if (pred_file != schet) {
                    printf("%s:", file->string[numb]);
                    pred_file = schet;
                  }
                }
                if (opt->n == 1) {
                  if (pred_schet != schet) {
                    printf("%d:", schet);
                    pred_schet = schet;
                  }
                }

                printf("%s\n", pattern->string[i]);
              }
              istr = strtok(NULL, " ");
            }
          }
          flag = 0;
        }
      }

      if (flag == 1 && global != 1 && opt->c == 0) {
        if ((opt->h == 0 && (file->number) > 1)) {
          printf("%s:", file->string[numb]);
        }
        if (opt->n == 1) {
          printf("%d:", schet);
        }
        printf("%s", search_string);

        if (opt->c == 0 && opt->l == 0) {
          int pr = 0;
          int y = strlen(search_string);
          for (int i = 0; i < y; i++) {
            if (search_string[y - 1] != '\n') {
              pr = 1;
            }
          }
          if (pr == 1) {
            printf("\n");
          }
        }
      }
      schet++;
    }

    if (opt->c == 1) {
      if ((opt->h == 0 && (file->number) > 1)) {
        printf("%s:", file->string[numb]);
      }
      printf("%d\n", counter);
    }

    if (opt->l == 1) {
      if (new_file == 1) {
        printf("%s\n", file->string[numb]);
      }
    }
  }
}
