#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./libft/gnl/gnl.h"

# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600
# define IMG_PXL 64
# define WND_NAME "Cub3d"
# define FOV 60.0f

# ifndef M_PI
    #  define M_PI 3.14159265358979323846
# endif

# define ERR_BAD_PATH 		"Error\nBad path map\n"
# define ERR_EMPTY_MAP 		"Error\nEmpty map\n"
# define ERR_ARGS 			"Error\nInvalid arguments\n"
# define ERR_SQUARE 		"Error\nInvalid square map\n"
# define ERR_WALLS 			"Error\nMissing walls map\n"
# define ERR_CHAR_MAP		"Error\nInvalid characters map\n"
# define ERR_PLY_NOT_FOUND	"Error\nPlayer not found\n"
# define ERR_MALLOC			"Error\nMalloc failed\n"
# define ERR_MLX			"Error\nMinilibx failed\n"

typedef enum	e_cardinals
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_cardinals;

typedef enum	e_move
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	ROT_RIGHT,
	ROT_LEFT
}	t_move;

typedef struct	s_wall
{
	float		distance;
	t_cardinals	orientation;
	float		hit_x;
	float		hit_y;
	float		texture_x;
}	t_wall;

typedef struct s_img
{
	char	*path;
	void	*img;
	char	*pxl_data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_player
{
	float	p_x;
	float	p_y;
	float	p_angle;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*wnd;
	char		*map_path;
	char		**map;
	char		**map_cpy;
	int			map_cpy_height;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	t_img		mlx_img;
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
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
void	ft_init_mlx(t_data *data);

// RAYCASTING

void	draw_ceiling(t_data *data, int x, int start_draw, int end_draw);
void	draw_floor(t_data *data, int x, int start_draw, int end_draw);
void	draw_wall(t_data *data, t_wall wall, int x, int start_draw, int end_draw);
void	load_textures(t_data *data);
void	render_loop(t_data *data);

#endif
