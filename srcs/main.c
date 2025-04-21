#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (perror(ERR_ARGS), 1);
	data = (t_data){0};
	data.path = argv[1];
	ft_init_data(&data, argv[1]);
	//ft_init_map(&data);
	return (0);
}
