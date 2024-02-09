CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f ./jogo
	rm -f main.o
