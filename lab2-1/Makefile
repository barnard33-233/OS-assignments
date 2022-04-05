# Makefile of Mysh
src_dir = ./src
inc_dir = ./include

# VPATH = $(src_dir) $(inc_dir)

SOURCE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.c))

INCLUDE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.h))

cflags = -I $(inc_dir) -Wall -o
testflags = -g -D DEBUG -I ./test $(cflags)

# testobj = test?*.o
# testsrc = 

default:
	make mysh

mysh:$(SOURCE) $(INCLUDE)
	gcc $(SOURCE) $(cflags) mysh

test1.o:$(SOURCE) $(INCLUDE) ./test/test1-0.c
	gcc ./test/test1-0.c $(SOURCE) $(testflags) test1.o

test2.o:$(SOURCE) $(INCLUDE) ./test/test2.c
	gcc ./test/test2.c $(SOURCE) $(testflags) test2.o

.PHONY: clean
clean:
	-rm ./mysh ./test*.o