# Nom de l'exécutable
NAME = minishell

# Répertoire contenant les sources

# Librairies à lier
LIBS = -lreadline

# Fichiers source
SRC = minishell.c \
      utils.c \
      shell_exec.c \
      parsing_pipe.c \
      tokenize.c \
      utilshelp.c \
      free.c \
      env.c \
      builtin.c \
	  ft_split.c \
	  builtin_help.c \
	  parsing_help.c \
	  init.c

# Fichiers objets générés automatiquement
OBJ = $(SRC:.c=.o)

# Compilateur et options
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Cible par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJ)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

# Règle générique pour compiler les .o
%.o: %.c
	@echo "💻 Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Cleaning object files..."
	$(RM) $(OBJ)

# Nettoyage complet
fclean: clean
	@echo "🧼 Cleaning executable..."
	$(RM) $(NAME)

# Rebuild complet
re: fclean all
