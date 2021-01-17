CFLAGS = -std=c99 -Wall -pedantic   
CC =gcc

all: tree.o


array.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o $@
	

clean: 
	rm -i  tree.o 
