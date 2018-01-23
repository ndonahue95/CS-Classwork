CC = gcc

OPTIONS = -Werror -Wall -std=c99

LIBS = -lm `pkg-config --cflags --libs gtk+-2.0`

all: ../lib/imageio.o bonus.c
	$(CC) $(OPTIONS) $(LIBS) -o bonus ../lib/imageio.o bonus.c

clean:
	rm -f bonus *.o
