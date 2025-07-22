#include "../../cub3d.h"

static void	ft_malloc_content(t_data *data)
{
	int		fd;
	char	*line;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		perror(ERR_EMPTY_MAP);
		exit(EXIT_FAILURE); //leak de la struct player
	}
	while (line)
	{
		data->map_copy_height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	data->map_copy = malloc(sizeof(char *) * (data->map_copy_height + 1));
	if (!data->map_copy)
		exit(EXIT_FAILURE);
}

void	ft_fill_content(t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	ft_malloc_content(data); //calcul lignes pour malloc
	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE); //leak player
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		data->map_copy[++i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->map_copy[i + 1] = NULL;
	free(line);
	close(fd);
}

static char	*ft_trim_map_line(char *line)
{
	int		i;
	int		j;
	char	*buffer;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	buffer = malloc(ft_strlen(line) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\r' && line[i] != '\t')
			buffer[j++] = line[i];
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

static int	ft_find_map_start(char **content, int end) //quid si je mets plusieurs lignes vides entre F&C config et le debut de map
{
	int		start;
	int		k;

	start = end;
	while (start >= 0)
	{
		k = 0;
		while (content[start][k] == ' ' || content[start][k] == '\t')
			k++;
		if (content[start][k] == '\0' || content[start][k] == '\n')
			start--;
		else if (ft_strchr("01NSEW", content[start][k]))
			start--;
		else
			break ;
	}
	return (start + 2);
}

void	ft_get_map(t_data *data)
{
	int		i;
	int		j;
	int		start;
	int		map_lines;
	char	**map;

	i = data->map_copy_height - 1;
	while (i >= 0 && data->map_copy[i][0] == '\n')
		i--;
	start = ft_find_map_start(data->map_copy, i); //trouve la ligne de debut de map
	map_lines = i - start + 1;
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		exit(EXIT_FAILURE); //leak player
	j = 0;
	while (j < map_lines)
	{
		map[j] = ft_trim_map_line(data->map_copy[start + j]);
		if (!map[j])
			exit(EXIT_FAILURE); //leak
		j++;
	}
	map[j] = NULL;
	data->map = map;
	data->map_height = map_lines;
}
