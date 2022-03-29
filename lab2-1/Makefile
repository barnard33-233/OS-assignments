# Makefile of Mysh
src_dir = ./src
inc_dir = ./include

# VPATH = $(src_dir) $(inc_dir)

SOURCE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.c))

INCLUDE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.h))

cflags = -g -I $(inc_dir) -Wall -o
testflags = -D DEBUG -I ./test $(cflags)

# testobj = test?*.o
# testsrc = 

mysh:$(SOURCE) $(INCLUDE)
	gcc $(SOURCE) $(cflags) mysh

# test option to finish
test1.o:$(SOURCE) $(INCLUDE) ./test/test1-0.c
	gcc ./test/test1-0.c $(SOURCE) $(testflags) test1.o

.PHONY: clean
clean:
	-rm ./mysh ./test*.o