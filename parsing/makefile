NAME = minishell

# Répertoires

# Fichiers source
SRC = $(SRC_DIR)minishell.c \
$(SRC_DIR)utils.c \
$(SRC_DIR)shell_exec.c \
$(SRC_DIR)split_pipe.c \
$(SRC_DIR)tokenize.c \
$(SRC_DIR)utilshelp.c \
$(SRC_DIR)free.c \
# Fichiers objets correspondants
OBJ = $(SRC:.c=.o)

# Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

# Cible par défaut
all: $(NAME)

# Créer l'exécutable
$(NAME): $(OBJ)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

# Règle pour compiler les fichiers objets
%.o: %.c
	@echo "💻 Compiling $<"
	$(CC) $(FLAGS) -c $< -o $@

# Nettoyer les fichiers objets
clean:
	@echo "🧹 Cleaning object files..."
	$(RM) $(OBJ)

# Supprimer les objets et l'exécutable
fclean: clean
	@echo "🧼 Cleaning everything..."
	$(RM) $(NAME)
# Recompiler tout
re: fclean all

