NAME = minishell

CC = clang -g
LD = clang -g
LDFLAGS = -lreadline -lhistory
CFLAGS = -Wall -Wextra -Iinclude

SRCS = main.c $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) $(wildcard parsing/*.c)
OBJ = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
