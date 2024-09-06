

#include "../Cub3D.h"

void	ft_map(int flag)
{
	if (!flag)
	{
		printf("The map not exist in the file_map!!\n");
		exit(EXIT_FAILURE);
	}
}
int ft_readline(t_map *map, char *line, int fd, int *flag)
{
	int	len;
	int	index_line;
	int	l_flag;

	len = 0;
	l_flag = 0;
	index_line = 1;
	while (line)
	{
		if (line[0] != '\n')
		{
			len++;
			if (len > 6)
			{
				l_flag = 1;
				check_linemap(map, line, index_line, flag);
			}
		}
		free(line);
		line = get_next_line(fd);
		index_line++;
	}
	ft_map(l_flag);
	close(fd);
	return (len);
}

int ft_lenmap(t_map *map , const char *path_map)
{
	int		len;
	int		fd;
	int		flag;
	char	*line;

	len = 0;
	flag = 0;
	fd = open(path_map,  O_RDONLY , 0644);
	if (fd == -1)
	{
		printf ("open() failed{check path_filemap, ..!}\n");
		exit(EXIT_FAILURE);
	}
	if (!(line = get_next_line(fd)))
	{
		printf("Empty file_map !!\n");
		exit(EXIT_SUCCESS);
	}
	len = ft_readline(map, line, fd, &flag);
	if (!flag)
	{
		printf("The player Not existance in the map !\n");
		exit(EXIT_FAILURE);
	}
	return (len);
}
int	ft_allocmap(t_map *map, char **av)
{
	int len_map;

	len_map = ft_lenmap(map, av[1]) - 6;
	map->tab_map = malloc((len_map + 1) * sizeof(char *));
	if (!map->tab_map)
	{
		printf("malloc failed !!\n");
		exit(EXIT_FAILURE);
	}
	map->tab_map[len_map] = NULL;
	return (len_map);
}