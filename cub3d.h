#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>

# define ERR_BAD_PATH "Error: Bad format path map\n"
# define ERR_ARGS "Error: Invalid arguments\n"

typedef enum e_move
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	ROT_RIGHT,
	ROT_LEFT
}	t_move;

typedef struct s_data
{
	char	*path;
	int		width;
	int		height;
	char	**map;
}	t_data;

void	ft_init_map(t_data *data, char *path);

#endif
