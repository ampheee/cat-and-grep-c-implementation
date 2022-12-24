CC =gcc
CFLAGS=-Wall	-Werror	-Wextra

all: cat

cat: cat.c	cat.h
	$(CC)	$(CFLAGS)	cat.c	-o cat

cat_rebuild:
	rm -rf cat
	make

checks:
	cppcheck --enable=all --suppress=missingIncludeSystem ../../src/cat/
	python3 ../../../../study/checks/cpplint.py --extensions=c *.c *h