CFLAGS = -std=c99 -Wall -pedantic D-DLIST  
CC =gcc

all: tree.o


array.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o $@
	

clean: 
	rm -i  tree.o 
