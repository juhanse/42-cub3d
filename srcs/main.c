#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		perror(ERR_ARGS);
		exit(EXIT_FAILURE);
	}
	ft_init_map(&data, argv[1]);
}
