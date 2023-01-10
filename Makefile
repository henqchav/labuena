CC=gcc
CFLAGS=-c -I.

alexa: main.o 
		$(CC) -o alexa main.o 

main.o: main.c 
		$(CC) $(CFLAGS) main.c


.PHONY: clean
clean:
		rm *.o alexa
		rm -rf programa *.o
		