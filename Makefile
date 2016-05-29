CFLAGS = -std=c99 -Wall -Wpedantic

ICLASSSRC = built-in-class.c cons.c environment.c macro.c package.c special_operator.c string.c subr.c symbol.c
ICLASSOBJ = $(ICLASSSRC:.c=.o)
ISOURCES = alloc.c dynvar.c error.c eval.c function.c ground.c global.c init.c list.c values.c
IOBJECTS = $(ISOURCES:.c=.o)

all: $(IOBJECTS) $(ICLASSOBJ)

test: $(IOBJECTS) $(ICLASSOBJ) test.o
	$(CC) $(CFLAGS) test.o $(IOBJECTS) $(ICLASSOBJ) -lgc -o test

clean:
	rm -f test *.o
