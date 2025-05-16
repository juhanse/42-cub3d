NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRCDIR = srcs/
OBJDIR = objs/
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

INIT = init/init.c init/fill_data.c init/parse_config.c init/parse_map.c init/utils.c
SRC = main.c $(INIT)

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFTDIR) -lft mlx/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
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
