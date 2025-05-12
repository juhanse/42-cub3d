#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./libft/gnl/gnl.h"
#include "./mlx/include/MLX42/MLX42.h"

# define ERR_BAD_PATH 	"Error\nBad path map\n"
# define ERR_ARGS 		"Error\nInvalid arguments\n"
# define ERR_SQUARE 	"Error\nInvalid square map\n"
# define ERR_WALLS 		"Error\nMissing walls map\n"

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
	char		*path;
	char		**content;
	char		**map;
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

// TEMP
void	ft_parsing(char *filepath, t_data *data);
void	read_file(char *path, t_data *data);
void	parse_config(t_data *data);
void	parse_map(t_data *data);
void	free_data(t_data *data);
int		parse_rgb(char *str);
int		is_map_line(char *line);

// PARSING
void	ft_debug(t_data *data);
void	ft_free(t_data *data);
void	ft_free_map(t_data *data);
void	ft_exit(char *msg);
void	ft_set_size(t_data *data);
void	ft_allocate_map(t_data *data);
void	ft_fill_map(t_data *data);
void	ft_init_map(t_data *data);
void	ft_init_data(t_data *data, char *path);

#endif
