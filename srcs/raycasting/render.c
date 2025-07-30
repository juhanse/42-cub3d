#include "../cub3d.h"

void	get_pxls_data(t_data *data) //should be proctected ?
{
	data->north.pxl_data = mlx_get_data_addr(data->north.img, &data->north.bpp, &data->north.size_line, &data->north.endian);
	data->south.pxl_data = mlx_get_data_addr(data->south.img, &data->south.bpp, &data->south.size_line, &data->south.endian);
	data->west.pxl_data = mlx_get_data_addr(data->west.img, &data->west.bpp, &data->west.size_line, &data->west.endian);
	data->east.pxl_data = mlx_get_data_addr(data->east.img, &data->east.bpp, &data->east.size_line, &data->east.endian);
}

void	load_fail(t_data *data)
{
	printf("Texture load failed.\n");
	ft_free_map(data); //better free needed
	exit (1);
}

void	load_textures(t_data *data)
{
	printf("=== DEBUGGING TEXTURE LOADING ===\n");
	printf("North path: '%s'\n", data->north.path ? data->north.path : "NULL");
	printf("South path: '%s'\n", data->south.path ? data->south.path : "NULL");
	printf("West path: '%s'\n", data->west.path ? data->west.path : "NULL");
	printf("East path: '%s'\n", data->east.path ? data->east.path : "NULL");
	
	printf("Loading north texture...\n");
	data->north.img = mlx_xpm_file_to_image(data->mlx, data->north.path, &data->north.width, &data->north.height);
	if (!data->north.img)
	{
		printf("❌ FAILED: North texture failed to load: %s\n", data->north.path);
		return (load_fail(data));
	}
	printf("✅ North texture loaded successfully\n");
	
	printf("Loading south texture...\n");
	data->south.img = mlx_xpm_file_to_image(data->mlx, data->south.path, &data->south.width, &data->south.height);
	if (!data->south.img)
	{
		printf("❌ FAILED: South texture failed to load: %s\n", data->south.path);
		return (load_fail(data));
	}
	printf("✅ South texture loaded successfully\n");
	
	printf("Loading west texture...\n");
	data->west.img = mlx_xpm_file_to_image(data->mlx, data->west.path, &data->west.width, &data->west.height);
	if (!data->west.img)
	{
		printf("❌ FAILED: West texture failed to load: %s\n", data->west.path);
		return (load_fail(data));
	}
	printf("✅ West texture loaded successfully\n");
	
	printf("Loading east texture...\n");
	data->east.img = mlx_xpm_file_to_image(data->mlx, data->east.path, &data->east.width, &data->east.height);
	if (!data->east.img)
	{
		printf("❌ FAILED: East texture failed to load: %s\n", data->east.path);
		return (load_fail(data));
	}
	printf("✅ East texture loaded successfully\n");
	
	printf("Getting pixel data...\n");
	get_pxls_data(data);
	printf("✅ All textures loaded successfully!\n");
}

// void	load_textures(t_data *data) //voir pour refactor avec une boucle ?
// {
// 	data->north.img = mlx_xpm_file_to_image(data->mlx, data->north.path, &data->north.width, &data->north.height);
// 	if (!data->north.img)
// 		return (load_fail(data));
// 	data->south.img = mlx_xpm_file_to_image(data->mlx, data->south.path, &data->south.width, &data->south.height);
// 	if (!data->south.img)
// 		return (load_fail(data));
// 	data->west.img = mlx_xpm_file_to_image(data->mlx, data->west.path, &data->west.width, &data->west.height);
// 	if (!data->west.img)
// 		return (load_fail(data));
// 	data->east.img = mlx_xpm_file_to_image(data->mlx, data->east.path, &data->east.width, &data->east.height);
// 	if (!data->east.img)
// 		return (load_fail(data));
// 	get_pxls_data(data);
// }

bool	is_wall(t_data *data, int map_x, int map_y)
{
	bool	hit;
	
	hit = false;
	if (data->map[map_y][map_x] == '1')
		hit = true;
	return (hit);
}

void inspect_wall(t_wall *wall, float current_x, float current_y, float distance, float ray_dir_x, float ray_dir_y, float step)
{
	const float	prev_x = current_x - ray_dir_x * step;
	//const float prev_y = current_y - ray_dir_y * step;

	wall->distance = distance;
	wall->hit_x = current_x;
	wall->hit_y = current_y;
	if ((int)prev_x != current_x)
	{
		wall->texture_x = current_y - (int)current_y;
		if (ray_dir_x > 0)
			wall->orientation = WEST;
		else
			wall->orientation = EAST;
	}
	else
	{
		wall->texture_x = current_x - (int)current_x;
		if (ray_dir_y > 0)
			wall->orientation = NORTH;
		else
			wall->orientation = SOUTH;
	}
}

t_wall	cast_ray(t_data *data, float ray_angle)
{
	t_wall		wall;
	float		current_x;
	float		current_y;
	float		distance;
	const float	ray_dir_x = cos(ray_angle);
	const float	ray_dir_y = sin(ray_angle);
	const float	step = 0.01f;

	wall = (t_wall){0};
	current_x = data->player->p_x;
	current_y = data->player->p_y;
	distance = 0.0f;
	while (1)
	{
		current_x += ray_dir_x * step;
		current_y += ray_dir_y * step;
		distance += step;
		if (is_wall(data, current_x, current_y))
		{
			inspect_wall(&wall, current_x, current_y, distance, ray_dir_x, ray_dir_y, step);
			break ;
		}
	}
	return (wall);
}

void	draw_pxl_col(t_data *data, int x, t_wall wall)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;

	wall_height = SCREEN_HEIGHT / wall.distance;
	wall_start = (SCREEN_HEIGHT - wall_height) / 2;
	wall_end = wall_start + wall_height;
	draw_ceiling(data, x, 0, wall_start);
	draw_wall(data, wall, x, wall_start, wall_end);
	draw_floor(data, x , wall_end, SCREEN_WIDTH);
}

void	render_3d(t_data *data)
{
	int		x;
	float	ray_angle;
	t_wall	wall;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_angle = data->player->p_angle + (x - SCREEN_WIDTH / 2) * (FOV / SCREEN_WIDTH);
		wall = cast_ray(data, ray_angle);
		draw_pxl_col(data, x, wall);
	}
}

int	render_loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_clear_window(data->mlx, data->wnd);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
	return (0);
}
