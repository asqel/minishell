NAME = minishell

CC = gcc -g
LD = gcc -g
LDFLAGS = -lreadline -lhistory #-fsanitize=address
CFLAGS = -Wall -Wextra -I. #-fsanitize=address

SRCS = main.c $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) $(wildcard Minishell_limit4000/*.c)
OBJ = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@ ..."
	@$(LD) -o $@ $^ $(LDFLAGS)

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

debug: $(NAME)
	@echo "Debugging $<"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.sup ./$(NAME)



.PHONY: all clean fclean re
