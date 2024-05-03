CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: my_mastermind

my_mastermind: main.o mastermind.o
	$(CC) $(CFLAGS) -o my_mastermind main.o mastermind.o

main.o: main.c mastermind.h
	$(CC) $(CFLAGS) -c main.c

mastermind.o: mastermind.c mastermind.h
	$(CC) $(CFLAGS) -c mastermind.c

clean:
	rm -f *.o

fclean: clean
	rm -f my_mastermind

re: fclean all
