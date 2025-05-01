NAME = minishell

CC = clang -g
LD = clang -g
LDFLAGS = -lreadline -lhistory
CFLAGS = -Wall -Wextra -I.

SRCS = main.c $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) $(wildcard parsing/*.c)
OBJ = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@ ..."
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing objects (.o) files"
	@rm -rf $(OBJ)

fclean: clean
	@echo "Removing executable $(NAME)"
	@rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re
