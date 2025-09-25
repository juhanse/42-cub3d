/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:06:29 by juhanse           #+#    #+#             */
/*   Updated: 2025/09/25 11:49:45 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#  define M_PI 3.14159265358979323846
# endif

# define WND_NAME "Cub3d"
# define SCRN_WIDTH 1280
# define SCRN_HEIGHT 720
# define SCRN_CENTER 360
# define SIZE 64
# define FOV 60.0f
# define SPEED 0.05f
# define ROT_SPEED 0.05f

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
# define MINI_Y MINI_MARGIN
# define P_SIZE 2

# define ERR_BAD_PATH 		"Error\nBad path map\n"
# define ERR_CONFIG 		"Error\nInvalid config\n"
# define ERR_MAP 			"Error\nInvalid map\n"
# define ERR_EMPTY_MAP 		"Error\nEmpty map\n"
# define ERR_ARGS 			"Error\nInvalid arguments\n"
# define ERR_CHAR_MAP		"Error\nInvalid characters map\n"
# define ERR_PLY_NOT_FOUND	"Error\nPlayer not found\n"
# define ERR_MALLOC			"Error\nMalloc failed\n"
# define ERR_DUP			"Error\nDuplicate found\n"
# define ERR_MISSING_TEXT	"Error\nMissing texture\n"

typedef struct s_mini
{
	int	mini_x; //minimap area x start pos
	int	scale;
	int	width_pxl;
	int	height_pxl;
	int	offset_x;
	int	offset_y;
	int	pxl_x;
	int	pxl_y;
	int	px; //player_x
	int	py; //player_y
	int	vision_length;
}	t_mini;

typedef struct s_wall
{
	int		wall_map_x;
	int		wall_map_y;
	int		texture_id;
	int		wall_start;
	int		wall_end;
	int		wall_height;
	int		wall_color;
	float	wall_dist;
	float	fixed_dist;
	float	wall_col;
}	t_wall;

typedef struct s_ray
{
	int		x_side; //-1 to the left & 1 to the right
	int		y_side;
	int		map_x;
	int		map_y;
	int		hit;
	float	start_x;
	float	start_y;
	float	dir_x;
	float	dir_y;
	float	delta_x; //const dist to cross one cell
	float	delta_y;
	int		wall_side;
	t_wall	wall;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*path;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		s_line;
	int		endian;
	int		text_x;
	int		text_y;
	float	text_step;
	float	text_yf;
}	t_img;

typedef struct s_keys
{
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
	bool	left_rot;
	bool	right_rot;
	int		mouse_x;
	int		mouse_y;
	int		last_mouse_x;
}	t_keys;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
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
	char		**map_tmp;
	char		**map;
	int			content_height;
	int			map_height;
	int			map_max_width;
	int			map_error;
	int			floor_color;
	int			ceiling_color;
	int			exit_code;
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
void	ft_free_map(t_data *data, int type);
void	ft_free_split(char **s);
void	ft_free_fill_map(t_data *data, int len);

// EXIT & FREE
int		exit_game(t_data *data);

// PARSING
int		ft_initialize(t_data *data, char *path);
int		ft_check_textures(t_data *data, char *s);
int		ft_check_colors(t_data *data, char *s);
int		ft_parse_rgb(char *str);
int		ft_fill_content(t_data *data);
int		ft_get_config_color(t_data *data);
int		ft_get_config_texture(t_data *data);
int		ft_fill_map(t_data *data);
int		ft_found_player(t_data *data);
void	ft_flood_fill(t_data *data, int x, int y);
int		ft_test_map(t_data *data);

// RAYCASTING
t_ray	cast_ray(t_data *data, float ray_angle);
t_img	*get_texture(t_data *data, int texture_id);
int		get_color(t_img *texture, int tex_x, int tex_y);
int		get_texture_id(int wall_side, int axis_side);
void	init_ray(t_ray *ray, t_player *player, float ray_angle);
void	play_game(t_data *data);
void	prep_texture(t_img *text, t_ray *ray);
void	put_pixel(t_data *data, int x, int y, int color);
void	normalize_angle(t_player *player);
void	reset_black(t_data *data);
int		render_loop(t_data *data);
void	render_minimap(t_data *data);
void	render_screen(t_data *data);
void	set_hooks(t_data *data);
void	update_player_dir(t_player *player);
void	update_text_y(t_img *text);
int		valid_move(t_data *data, float x, float y);

// MINIMAP
void	draw_cell(t_data *data, int m_x, int m_y);
void	draw_vision_ray(t_data *data, t_mini *mini);
int		is_player(char c);
void	put_mini_pixel(t_data *data, int x, int y, int color);;
int		set_scale(t_data *data);

#endif
