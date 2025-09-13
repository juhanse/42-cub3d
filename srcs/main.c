#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (perror(ERR_ARGS), 1);
	data = (t_data){0};
	if (ft_initialize(&data, argv[1]))
		return (1);
	//play_game(&data);
	return (0);
}
