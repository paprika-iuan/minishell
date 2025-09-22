NAME = minishell
SRC = src/main.c \
		src/builtins/echo.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADER_DIR = inc
HEADER = $(HEADER_DIR)/minishell.h

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
CCFLAGS = -Wall -Wextra -g
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT): libft

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -I. -Ilibft -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re libft
