NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

HEADER = libft.h
SOURCES_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_FILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

LIBFT_OBJS = $(SOURCES_FILES:.c=.o)
LIBFT_OBJS_BONUS = $(BONUS_FILES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(HEADER)
	ar rcs $(NAME) $(LIBFT_OBJS)
	@echo "$(COLOUR_GREEN)Libft compiled ✅$(COLOUR_END)"

bonus: $(NAME) $(LIBFT_OBJS_BONUS)
	ar rcs $(NAME) $(LIBFT_OBJS_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBFT_OBJS) $(LIBFT_OBJS_BONUS)
	@echo "$(COLOUR_RED)Libft cleaned 🧹$(COLOUR_END)"

fclean: clean
	rm -f $(NAME)
	@echo "$(COLOUR_RED)Libft cleaned all 🧹$(COLOUR_END)"

re: fclean all

.PHONY: all bonus clean fclean re
