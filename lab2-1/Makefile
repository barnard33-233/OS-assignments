# Makefile of Mysh
src_dir = ./src
inc_dir = ./include

# VPATH = $(src_dir) $(inc_dir)

SOURCE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.c))

INCLUDE = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.h))

cflags = -I $(inc_dir) -Wall -o

mysh:$(SOURCE) $(INCLUDE)
	gcc $(SOURCE) $(cflags) mysh

# test option to finish

.PHONY: clean
clean:
	-rm ./mysh