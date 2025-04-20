#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

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
	char	**map;
}	t_data;

#endif
