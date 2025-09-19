#include "../../cub3d.h"

static int	handle_text(t_data *data, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Texture load failed: %s\n", path);
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->s_line, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

static int	upload_textures(t_data *data)
{
	if (handle_text(data, &data->north, data->north.path))
		return (1);
	if (handle_text(data, &data->south, data->south.path))
		return (1);
	if (handle_text(data, &data->west, data->west.path))
		return (1);
	if (handle_text(data, &data->east, data->east.path))
		return (1);
	return (0);
}

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->wnd = mlx_new_window(data->mlx, SCRN_WIDTH, SCRN_HEIGHT, WND_NAME);
	if (!data->wnd)
		return (1);
	data->mlx_img.img = mlx_new_image(data->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	if (!data->mlx_img.img)
		return (1);
	data->mlx_img.data = mlx_get_data_addr(data->mlx_img.img,
			&data->mlx_img.bpp, &data->mlx_img.s_line, &data->mlx_img.endian);
	if (!data->mlx_img.data)
		return (1);
	mlx_put_image_to_window(data->mlx, data->wnd, data->mlx_img.img, 0, 0);
	return (0);
}

void	test_color_format(t_data *data)
{
	t_img	*texture;
	int		index;
	unsigned char r, g, b;
	
	// Prendre la première texture comme test
	texture = &data->north;
	index = 0; // Premier pixel
	
	printf("=== TEST FORMAT COULEUR ===\n");
	printf("Premier pixel de la texture:\n");
	printf("Byte 0: 0x%02X\n", (unsigned char)texture->data[index + 0]);
	printf("Byte 1: 0x%02X\n", (unsigned char)texture->data[index + 1]);
	printf("Byte 2: 0x%02X\n", (unsigned char)texture->data[index + 2]);
	printf("Byte 3: 0x%02X\n", (unsigned char)texture->data[index + 3]);
	
	// Test BGR (format actuel)
	b = texture->data[index + 0];
	g = texture->data[index + 1];
	r = texture->data[index + 2];
	printf("Format BGR: R=0x%02X G=0x%02X B=0x%02X\n", r, g, b);
	
	// Test RGB (format alternatif)
	r = texture->data[index + 0];
	g = texture->data[index + 1];
	b = texture->data[index + 2];
	printf("Format RGB: R=0x%02X G=0x%02X B=0x%02X\n", r, g, b);
	
	printf("Regardez votre texture et comparez avec ces valeurs!\n");
}

void	play_game(t_data *data)
{
	if (init_mlx(data) || upload_textures(data))
		exit_game(data);
	test_color_format(data);
	set_hooks(data);
	mlx_loop(data->mlx);
}
