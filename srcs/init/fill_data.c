#include "../../cub3d.h"

static void	ft_malloc_content(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		data->content_len++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->content = malloc(sizeof(char *) * (data->content_len + 1));
	if (!data->content)
		exit(EXIT_FAILURE);
}

void	ft_fill_content(t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	ft_malloc_content(data);
	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		data->content[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->content[i + 1] = NULL;
	free(line);
	close(fd);
}

static char	*ft_trim_map_line(char *line)
{
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(ft_strlen(line) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			buffer[j] = line[i];
			j++;
		}
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

void	ft_get_map(t_data *data)
{
	int		i = data->content_len - 1;
	int		map_lines = 0;
	char	**map;

	// Rechercher la dernière ligne de la map
	while (i >= 0 && data->content[i][0] == '\n')
		i--;

	// Trouver le début de la map
	int	start = i;
	while (start >= 0)
	{
		char *line = data->content[start];
		int	k = 0;

		// Skip whitespaces
		while (line[k] && (line[k] == ' ' || line[k] == '\t'))
			k++;

		// Si la ligne est vide, continue
		if (line[k] == '\0' || line[k] == '\n')
			start--;
		// Si la ligne commence par 0/1/N/S/E/W, c'est une ligne de map
		else if (ft_strchr("01NSEW", line[k]))
			start--;
		else
			break;
	}
	start++; // Ajuster après la dernière non-map line

	// Ignorer la première ligne de la map
	start++;

	map_lines = i - start + 1;
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		exit(EXIT_FAILURE);

	int j = 0;
	while (j < map_lines)
	{
		map[j] = ft_trim_map_line(data->content[start + j]);
		if (!map[j])
			exit(EXIT_FAILURE);
		j++;
	}
	map[j] = NULL;
	data->map = map;
}
