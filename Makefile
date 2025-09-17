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

PARSING = 	parsing/fill_content.c	\
			parsing/fill_map.c 		\
			parsing/flood_fill.c 	\
			parsing/init.c			\
			parsing/parse_config.c 	\
			parsing/parse_map.c 	\
			parsing/utils.c			\

RAYCASTING = 	raycasting/cast_ray.c		\
				raycasting/draw.c			\
				raycasting/mini_map.c		\
				raycasting/mini_utils.c		\
				raycasting/mlx_hooks.c		\
				raycasting/play_game.c		\
				raycasting/render_loop.c	\
				raycasting/render_screen.c	\
				raycasting/texture_utils.c	\
				raycasting/utils.c			\

SRC = main.c exit_free.c $(PARSING) $(RAYCASTING)

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
