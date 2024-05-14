CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = my_mastermind.c
OBJ = $(SRC:.c=.o)
EXEC = my_mastermind

.PHONY: all clean fclean re

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all