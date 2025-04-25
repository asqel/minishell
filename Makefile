NAME = minishell

CC = clang -g
LD = clang -g
LDFLAGS = -lreadline -lhistory
CFLAGS = -Wall -Wextra -I.

SRCS = main.c $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) $(wildcard parsing/*.c)
OBJ = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling and linking $@"
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
