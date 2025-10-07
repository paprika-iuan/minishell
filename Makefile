NAME = minishell
SRC = src/main.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/builtins/utils_env.c \
		src/errors/errors.c \
		src/executor/exec_tests.c \
		src/executor/execute_and_or.c \
		src/executor/execute_ast.c \
		src/executor/execute_pipe_sequence.c \
		src/executor/pipe_utils.c \
		src/executor/set_cmd_path.c \
		src/executor/execute_command.c \
		src/lexer/lexer.c \
		src/lexer/lexer_counter.c \
		src/lexer/lexer_utils.c \
		src/lexer/identifier.c \
		src/lexer/token_utils.c \
		src/parser/parse_ao.c \
		src/parser/parse_cmd.c \
		src/parser/parse_pipe.c \
		src/parser/parse_redirections.c \
		src/parser/parse_subshell.c \
		src/parser/parse_utils.c \
		src/parser/parser.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADER_DIR = inc
HEADER = $(HEADER_DIR)/minishell.h \
		$(HEADER_DIR)/parser.h

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
	$(CC) $(CCFLAGS) -I $(HEADER_DIR)/ -Ilibft -c $< -o $@

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
