NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRCDIR = srcs/
OBJDIR = objs/
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

TMP = parsing/parsing.c parsing/parse_config.c parsing/parse_map.c
PARSING = parsing/init_data.c parsing/init_map.c parsing/fill_map.c
SRC = main.c utils.c $(TMP)

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) -o $(NAME) -L$(LIBFTDIR) -lft
	@echo "$(COLOUR_GREEN)Cub3d compiled ✅$(COLOUR_END)"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(LIBFTDIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)
	@echo "$(COLOUR_RED)Cub3d cleaned 🧹$(COLOUR_END)"

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(RM) $(NAME)
	@echo "$(COLOUR_RED)Cub3d cleaned all 🧹$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
