CFLAGS=-Wall -g

all: ex19 ex19_alt

ex19: ex19.o object.o game.o
	$(CC) $(CFLAGS) ex19.o object.o game.o -o ex19

ex19_alt: ex19_alt.o object.o game.o
	$(CC) $(CFLAGS) ex19_alt.o object.o game.o -o ex19_alt

test: ex19
	./test.sh

clean:
	rm -f ex19 ex19_alt *.o
