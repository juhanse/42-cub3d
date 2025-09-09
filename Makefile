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

INIT = init/init.c init/fill_map.c init/parse_config.c init/parse_map.c init/utils.c
RAYCASTING = raycasting/play_game.c raycasting/render_loop.c raycasting/utils.c raycasting/render_screen.c raycasting/draw.c raycasting/mini_new.c
SRC = main.c $(INIT) $(RAYCASTING)

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFTDIR) -lft -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
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
