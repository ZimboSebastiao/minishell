NAME		= minishell

SRC_DIR		= sources
OBJ_DIR		= obj
INC_DIR		= includes
LIB_DIR		= lib
LIBFT_DIR	= $(LIB_DIR)/libft1

MAIN_SRC	= main.c
SRC_FILES	= $(MAIN_SRC) \
			  $(wildcard $(SRC_DIR)/*.c) \
			  $(wildcard $(SRC_DIR)/*/*.c) \
			  $(wildcard $(SRC_DIR)/*/*/*.c)

OBJ_FILES	= $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $(NAME)
	@echo "🐚 Minishell compilado com $(words $(SRC_FILES)) arquivos fonte"

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "📚 Libft compilada"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test:
	@bash tests/ft_test.sh

test-valgrind:
	@valgrind --leak-check=full ./$(NAME) < tests/ft_test.sh

val:
	@valgrind -q\
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--trace-children=yes \
		--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
		--suppressions=./valgrind.supp \
		./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@echo "🧹 Objetos removidos"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@echo "🗑️  Tudo limpo"

re: fclean all

info:
	@echo "📁 Arquivos fonte encontrados:"
	@for file in $(SRC_FILES); do echo "   $$file"; done
	@echo "📦 Total: $(words $(SRC_FILES)) arquivos"

.PHONY: all clean fclean re info
