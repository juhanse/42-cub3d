#include "../../cub3d.h"

void	free_content(char **content)
{
	int	i = 0;
	while (content && content[i])
		free(content[i++]);
	free(content);
}

void	free_data(t_data *data)
{
	free_content(data->map);
	free(data->north_image);
	free(data->south_image);
	free(data->west_image);
	free(data->east_image);
	free(data->player);
}

void	read_file(char *path, t_data *data)
{
	int		fd, i = 0;
	char	*line;
	char	**lines = malloc(sizeof(char *) * 1000); // ou compte les lignes avant

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while ((line = get_next_line(fd)))
	{
		lines[i++] = ft_strtrim(line, "\n");
		free(line);
	}
	lines[i] = NULL;
	data->content = lines;
	close(fd);
}

void	ft_parsing(char *filepath, t_data *data)
{
	read_file(filepath, data);
	parse_config(data);
	parse_map(data);
	free_content(data->content);
}
