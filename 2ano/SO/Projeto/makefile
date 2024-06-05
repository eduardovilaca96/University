CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = 

all: folders orchestrator client

orchestrator: bin/orchestrator

client: bin/client

folders:
		@mkdir -p src include obj bin tmp

bin/orchestrator: obj/orchestrator.o
		$(CC) $(LDFLAGS)-o bin/orchestrator src/orchestrator.c

bin/client: obj/client.o
		$(CC) $(LDFLAGS) -o bin/client src/client.c

obj/%.o: src/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -f obj/* tmp/* bin/*