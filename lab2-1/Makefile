objects = shell.o
src_dir = ./src
include_dir = ./include
cflags = -I $(include_dir) -c

mysh:$(objects)
	gcc $(objects) -o mysh

shell.o:$(src_dir)/shell.c $(include_dir)/shell.h
	gcc $(cflags) $(src_dir)/shell.c -o shell.o


.PHONY: clean
clean:
	-rm ./*.o mysh