CC =gcc
CFLAGS=-Wall	-Werror	-Wextra

all: grep

grep: grep.c	grep.h
	$(CC)	$(CFLAGS)	grep.c	-o grep

grep_rebuild:
	rm -rf grep
	make

grep_test: