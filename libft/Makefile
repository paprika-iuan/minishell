# Main Makefile for libft project

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

# Directories
OBJ_DIR = obj

# Library name
NAME = libft.a

# Source files
SRCS =	ft_atoi.c \
	ft_atol.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_conversions.c \
	ft_conversions_num.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isquote.c \
	ft_iswhitespace.c \
	ft_itoa.c \
	ft_max.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_min.c \
	ft_printf.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strndup.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c

BONUS_SRCS =	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c


# Object files - convert path from ft_*.c to obj/ft_*.o
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

BONUS_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

# Default target
all: $(NAME)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Create the library
$(NAME): $(OBJS)
	ar rcs $@ $^
	@echo "Library $(NAME) created successfully!"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned."

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "Library $(NAME) removed."

# Rebuild everything
re: fclean all

# Add bonus functions to the library
bonus: $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)
	@echo "Bonus object files added to $(NAME)!"

# Include dependency files
-include $(OBJS:.o=.d)
-include $(BONUS_OBJS:.o=.d)

# Declare phony targets
.PHONY: all clean fclean re bonus
