#include "grep.h"

struct grep pattern = {0};
struct grep file = {0};

void parse_Opts(int argc, char **argv, opts *options) {
  const char *short_Opts = "e:ivclnhsf:o";
  int flag;
  while ((flag = getopt_long(argc, argv, short_Opts, NULL, NULL)) != -1)
    switch (flag) {
      case 'e':
        options->eFlag = true;
        get_pattern(optarg);
        break;
      case 'i':
        options->iFlag = true;
        break;
      case 'v':
        options->vFlag = true;
        break;
      case 'c':
        options->cFlag = true;
        break;
      case 'l':
        options->lFlag = true;
        break;
      case 'n':
        options->nFlag = true;
        break;
      case 'h':
        options->hFlag = true;
        break;
      case 's':
        options->sFlag = true;
        break;
      case 'f':
        options->fFlag = true;
        get_pattern_from_file(optarg, argv);
        break;
      case 'o':
        options->oFlag = true;
        break;
      default:
        dprintf(STDERR_FILENO, "%s", errStr);
        exit(0);
    }
}

void get_pattern(const char *string) {
  strcpy(pattern.id[pattern.counter++], string);
}

void get_pattern_from_file(const char *name, char **argv) {
  FILE *f = fopen(name, "r");
  if (f) {
    for (char ch = getc(f); !feof(f); pattern.counter++, ch = getc(f)) {
      size_t pos = 0;
      pattern.id[pattern.counter][pos++] = ch;
      while (ch != '\n' && !feof(f)) {
        pattern.id[pattern.counter][pos++] = ch;
        ch = getc(f);
      }
    }
    fclose(f);
  } else {
    printf("%s: %s: No such file or directory\n", argv[0], name);
    exit(0);
  }
}

void match_patterns(char *str, opts *options) {
  size_t res = 0, fFile = 0, fNum = 0;
  regmatch_t pmatch[1] = {0};
  regex_t preg = {0};

  for (size_t current = 0; current < pattern.counter; current++) {
    if (regcomp(&preg, pattern.id[current],
                options->iFlag ? REG_EXTENDED | REG_NEWLINE | REG_ICASE
                               : REG_EXTENDED | REG_NEWLINE)) {
      continue;
    }
    if (options->oFlag && !options->lFlag && !options->vFlag &&
        !options->cFlag) {
      while (!regexec(&preg, str, 1, pmatch, 0)) {
        if (fFile++ == 0) {
          if (options->files > 1 && !options->hFlag) {
            printf("%s:", file.id[file.counter - 1]);
          }
        }
        if (options->nFlag && fNum++ == 0) printf("%d:", options->n);
        printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
               str + pmatch[0].rm_so);
        str += pmatch[0].rm_eo;
      }
    } else if (regexec(&preg, str, 0, pmatch, 0) == options->vFlag) {
      res++;
    }
    regfree(&preg);
  }

  if (res == pattern.counter || (res && !options->vFlag)) {
    if (options->cFlag) options->c++;
    if (options->lFlag) options->l = 1;
    if (!options->cFlag && !options->lFlag) {
      if (options->files > 1 && !options->nFlag) {
        printf("%s:", file.id[file.counter - 1]);
      }
      if (options->nFlag) printf("%d:", options->n);
      printf("%s\n", str);
    }
  }
}

void print_By_Flags(opts options) {
  if (options.oFlag && !options.lFlag && !options.vFlag && !options.cFlag)
    return;
  if (options.cFlag == 1) {
    if (options.files > 1 && !options.hFlag) {
      printf("%s:", file.id[file.counter - 1]);
    }
    printf("%d\n", options.c);
  }
  if (options.lFlag && options.l) {
    printf("%s\n", file.id[file.counter - 1]);
  }
}

void grep(const char *name, opts *options, char **argv) {
  FILE *f = fopen(name, "r");
  if (f) {
    strcpy(file.id[file.counter++], name);
    handle_file(f, options);
    fclose(f);
  } else if (!options->sFlag) {
    printf("%s: %s: No such file or directory\n", argv[0], name);
  }
}

void handle_file(FILE *f, opts *options) {
  char str[1000] = "";
  options->c = options->l = options->n = 0;
  for (char ch = getc(f); !feof(f); ch = getc(f)) {
    options->n++;
    size_t pos = 0;
    str[pos] = ch;
    while (ch != '\n' && !feof(f)) {
      str[pos++] = ch;
      ch = getc(f);
    }
    str[pos] = '\0';
    match_patterns(str, options);
    if (options->l == 1) break;
  }
  print_By_Flags(*options);
}

int main(int argc, char **argv) {
  if (argc >= 3) {
    opts options = {
        .eFlag = false,
        .iFlag = false,
        .vFlag = false,
        .cFlag = false,
        .lFlag = false,
        .nFlag = false,
        .hFlag = false,
        .sFlag = false,
        .fFlag = false,
        .oFlag = false,
    };
    for (int i = 0; i < 300; i++) {
      memset(&pattern.id[i], 0, 300);
    }
    parse_Opts(argc, argv, &options);
    if (!options.eFlag && !options.fFlag) get_pattern(argv[optind++]);
    options.files = argc - optind;
    while (optind < argc) {
      grep(argv[optind++], &options, argv);
    }
  } else {
    dprintf(STDERR_FILENO, "%s", errStr);
    exit(0);
  }
}
