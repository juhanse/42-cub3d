#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		perror(ERR_ARGS);
		return (1);
	}
	ft_init_map(&data, argv[1]);
	ft_debug(&data);
	return (0);
}
