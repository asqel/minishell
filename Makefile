NAME = minishell

CC = clang
LD = clang
LDFLAGS = -lreadline -lhistory
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCS = main.c $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c)
OBJ = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
