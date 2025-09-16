#include "../../cub3d.h"

int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	int	index;
	int	color;

	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	index = tex_y * texture->s_line + tex_x * (texture->bpp / 8);
	color = (texture->data[index + 2] << 16)
		| (texture->data[index + 1] << 8)
		| (texture->data[index + 0]);
	return (color);
}

int	get_texture_id(int wall_side, int axis_side)
{
	if (wall_side == 0)
	{
		if (axis_side > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (axis_side > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

t_img	*get_texture(t_data *data, int texture_id)
{
	if (texture_id == NORTH)
		return (&data->north);
	else if (texture_id == SOUTH)
		return (&data->south);
	else if (texture_id == WEST)
		return (&data->west);
	else if (texture_id == EAST)
		return (&data->east);
	return (&data->north);
}
