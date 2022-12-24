#include "cat.h"

void Cat(int file_Desc, const char *name, opts options, int *count) {
  if (file_Desc == -1) {
    char error[100];
    snprintf(error, sizeof(error), "%s %s", "./cat:", name);
    perror(error);
  }
  char buff[4096];
  memset(&buff[0], 0, sizeof(buff));
  int b_Read = read(file_Desc, buff, 4096);
  while (b_Read > 0) {
    int iterator = 0, emptyCount = 0, prev_ch = '\n';
    int ch = buff[iterator];
    while (true) {
      ch = buff[iterator];
      unsigned char next_ch = buff[iterator + sizeof(unsigned char)];
      if (ch == '\0' && next_ch == '\0') {
        break;
      }
      if (options.sFlag && ch == '\n' && prev_ch == '\n') {
        emptyCount++;
        if (emptyCount > 1) {
          iterator++;
          continue;
        }
      } else {
        emptyCount = 0;
      }
      if (((options.bFlag && ch != '\n') || options.nFlag) && prev_ch == '\n' &&
          ch != '\0') {
        *count += 1;
        printf("%6d\t", *count);
      }
      if (options.eFlag && ch == '\n') {
        printf("$");
      }
      if (options.tFlag && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (options.vFlag) {
        if ((ch >= 0x00 && ch < 0x09) || (ch >= 0x0B && ch <= 0x1F)) {
          printf("^");
          ch += 64;
        }
        if (ch == 0x7F) {
          printf("^");
          ch = '?';
        }
        if ((unsigned char)ch >= 0x80 && (unsigned char)ch <= 0x9F) {
          printf("M-^");
          ch -= 64;
        }
      }
      printf("%c", ch);
      prev_ch = ch;
      iterator++;
    }
    memset(&buff[0], 0, sizeof(buff));
    b_Read = read(file_Desc, buff, 4096);
  }
}

bool parse_Opts(int argc, char **argv, opts *options) {
  const char *short_Opts = "bestnvTE";
  const struct option long_Opts[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  int option, opt_Index = 0, err = 0;
  while ((option = getopt_long(argc, argv, short_Opts, long_Opts,
                               &opt_Index)) != -1) {
    switch (option) {
      case 'T':
        options->tFlag = true;
        break;
      case 'E':
        options->eFlag = true;
        break;
      case 'b':
        options->bFlag = true;
        break;
      case 'e':
        options->eFlag = true;
        options->vFlag = true;
        break;
      case 's':
        options->sFlag = true;
        break;
      case 't':
        options->tFlag = true;
        options->vFlag = true;
        break;
      case 'n':
        options->nFlag = true;
        break;
      case 'v':
        options->vFlag = true;
        break;
      default:
        dprintf(STDERR_FILENO, "%s", "usage: ./cat [-bestnvTE] [file...]");
        err = 1;
        return err;
    }
  }
  return err;
}

int main(int argc, char **argv) {
  if (argc >= 1) {
    opts options = {
        .bFlag = false,
        .eFlag = false,
        .sFlag = false,
        .tFlag = false,
        .nFlag = false,
        .vFlag = false,
    };
    bool error = parse_Opts(argc, argv, &options);
    int c = 0;
    if (!(argv[optind]) && error != true) {
      Cat(STDIN_FILENO, argv[0], options, &c);
    }
    if (error != true) {
      if (options.bFlag) {
        options.nFlag = false;
      }
      while (optind < argc) {
        Cat(open(argv[optind], O_RDONLY), argv[optind], options, &c);
        optind++;
        c = 0;
      }
    }
  } else {
    char error[100] = "./cat: ";
    perror(error);
  }
  return 0;
}
