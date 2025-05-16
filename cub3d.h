#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./libft/gnl/gnl.h"
// #include "./mlx/include/MLX42/MLX42.h"

# define ERR_BAD_PATH 		"Error\nBad path map\n"
# define ERR_ARGS 			"Error\nInvalid arguments\n"
# define ERR_SQUARE 		"Error\nInvalid square map\n"
# define ERR_WALLS 			"Error\nMissing walls map\n"
# define ERR_CHAR_MAP		"Error\nInvalid characters map\n"
# define ERR_PLY_NOT_FOUND	"Error\nPlayer not found\n"

typedef enum e_move
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	ROT_RIGHT,
	ROT_LEFT
}	t_move;

typedef struct s_player
{
	int	x;
	int	y;
	int	angle;
}	t_player;

typedef struct s_data
{
	char		*map_path;
	char		**content;
	char		**map;
	int			content_len;
	int			width;
	int			height;
	int			floor_color;
	int			ceiling_color;
	char		*north_image;
	char		*south_image;
	char		*west_image;
	char		*east_image;
	t_player	*player;
}	t_data;

// UTILS
void	ft_debug(t_data *data);
void	ft_exit(char *msg);
void	ft_free_map(t_data *data);
void	ft_print_map(t_data *data);

// INIT
int		ft_initialize(t_data *data, char *path);
void	ft_fill_content(t_data *data);
void	ft_get_config_color(t_data *data);
void	ft_get_config_texture(t_data *data);
void	ft_get_map(t_data *data);
int		ft_found_player(t_data *data);
int		ft_check_walls(t_data *data);
int		ft_check_char(t_data *data);

#endif
