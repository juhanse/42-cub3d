#include "../../cub3d.h"

/* where are we on the texture x and y wise */
void	prep_texture(t_img *text, t_ray *ray)
{
	text->text_x = (int)(ray->wall.wall_col * text->width);
	if (text->text_x >= text->width)
		text->text_x = text->width - 1;
	text->text_step = (float)text->height / ray->wall.wall_height;
	text->text_yf = (ray->wall.wall_start - SCRN_CENTER
			+ ray->wall.wall_height / 2) * text->text_step;
}

void	update_text_y(t_img *text, t_ray *ray)
{
	text->text_y = (int)text->text_yf;
	if (text->text_y >= text->height)
		text->text_y = text->height - 1;
	if (text->text_y < 0)
		text->text_y = 0;
}

int	get_color(t_img *texture, int tex_x, int tex_y)
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
