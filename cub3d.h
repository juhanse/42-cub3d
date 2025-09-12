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

# ifndef M_PI
  # define M_PI 3.14159265358979323846
# endif

# define WND_NAME "Cub3d"
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define SCREEN_CENTER (SCREEN_HEIGHT/2)
# define SIZE 64
# define FOV 60.0f
# define RAD_FOV (FOV*M_PI/180.0f)
# define SPEED 0.05f
# define ROT_SPEED 0.05f
# define STEP 0.5f
# define MAX_DIST 600.0f

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define MINI_SIZE 200
# define MINI_MARGIN 10
# define MINI_X (SCREEN_WIDTH - MINI_SIZE - MINI_MARGIN)
# define MINI_Y MINI_MARGIN
# define P_SIZE 2

# define ERR_BAD_PATH 		"Error\nBad path map\n"
# define ERR_MAP 			"Error\nInvalid map\n"
# define ERR_EMPTY_MAP 		"Error\nEmpty map\n"
# define ERR_ARGS 			"Error\nInvalid arguments\n"
# define ERR_SQUARE 		"Error\nInvalid square map\n"
# define ERR_WALLS 			"Error\nMissing walls map\n"
# define ERR_CHAR_MAP		"Error\nInvalid characters map\n"
# define ERR_PLY_NOT_FOUND	"Error\nPlayer not found\n"
# define ERR_MALLOC			"Error\nMalloc failed\n"
# define ERR_MLX			"Error\nMinilibx failed\n"

// typedef enum	e_cardinals
// {
// 	NORTH,
// 	SOUTH,
// 	WEST,
// 	EAST
// }	t_cardinals;

typedef struct s_mini
{
	int scale;
	int	width_pxl;
	int	height_pxl;
	int offset_x;
	int offset_y;
	int	pxl_x;
	int	pxl_y;
	int	px;
	int py;
}	t_mini;


typedef struct	s_wall
{
	int		wall_map_x;
	int		wall_map_y;
	int		texture_id;
	float	wall_dist;
	float	fixed_dist; //anti fisheye
	float	wall_col;
}	t_wall;

typedef struct s_ray
{
	int		x_side; // -1 a gauche || 1 a droite
	int		y_side; // -1 vers le haut || 1 vers le bas
	int		map_x;
	int		map_y;
	int		hit;
	float	start_x;
	float	start_y;
	float	dir_x;
	float	dir_y;
	float	delta_x; //distance constante pour traverser 1 case
	float	delta_y;
	int		wall_side;
	t_wall	wall;
}	t_ray;


typedef struct s_img
{
	char	*path;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_keys
{
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
	bool	left_rot;
	bool	right_rot;
}	t_keys;


typedef struct s_player
{
	float	p_x;
	float	p_y;
	float	p_angle;
	float	x_dir;
	float	y_dir;
	float	x_perp;
	float	y_perp;
	t_keys	moves;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*wnd;
	char		*map_path;
	char		**content;
	char		**map;
	int			content_height;
	int			map_height;
	int			map_max_width;
	int			floor_color;
	int			ceiling_color;
	t_img		mlx_img;
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
	t_mini		*minimap;
	t_player	*player;
}	t_data;

// UTILS
void	ft_debug(t_data *data);
void	ft_exit(char *msg);
void	ft_free_map(t_data *data);
void	ft_free_split(char **s);

// EXIT & FREE
int		quit_game(t_data *data);

// INIT
int		ft_initialize(t_data *data, char *path);
int		ft_fill_content(t_data *data);
void	ft_get_config_color(t_data *data);
void	ft_get_config_texture(t_data *data);
int		ft_get_map(t_data *data);
int		ft_found_player(t_data *data);
int		ft_check_walls(t_data *data);
int		ft_check_char(t_data *data);
void	ft_flood_fill(t_data *data, int x, int y);

// RAYCASTING
int		get_color(int texture_id);
void	normalize_angle(t_player *player);
void	play_game(t_data *data);
void	put_mini_pixel(t_data *data, int x, int y, int color);
void	put_pixel(t_data *data, int x, int y, int color);
void	reset_black(t_data *data);
int		render_loop(t_data *data);
void	render_minimap(t_data *data);
void	render_screen(t_data *data);
void	update_player_dir(t_player *player);
int		valid_move(t_data *data, float x, float y);

#endif
