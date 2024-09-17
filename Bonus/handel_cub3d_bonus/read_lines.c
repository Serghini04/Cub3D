/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/17 12:32:23 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	run_error(t_map *map, char *line, int j)
{
	if (is_sp(line, 0))
		printf ("The map must be closed by character '1'! \n");
	else
		printf ("Empty line in the map !\n");
	free_myallocation(map, j + 1);
	exit(EXIT_SUCCESS);
}

void	read_lines(t_map *map, int fd, int len_map)
{
	char		*line;
	static int	index_line;
	int			i;
	int			j;

	i = 0;
	j = -1;
	line = get_next_line(fd);
	while (line && ++index_line)
	{
		if (line[0] != '\n')
		{
			if (i < 6)
				ft_check_line(line, index_line, map);
			else if (i >= 6)
				map->tab_map[++j] = ft_strdup(line);
			i++;
		}
		else if (j >= 0 && i < len_map + 6 && is_sp(line, 0))
			run_error(map, line, j);
		free (line);
		line = get_next_line(fd);
	}
}

int	check_input(char **av, t_map *map)
{
	int	fd;
	int	len_map;

	check_namefile(av[1]);
	len_map = ft_allocmap(map, av);
	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		printf ("open() failed ! maby Pathfile_map'%s' not existed!\n", av[1]);
		free(map->tab_map);
		exit(EXIT_FAILURE);
	}
	read_lines(map, fd, len_map);
	close(fd);
	return (len_map);
}

void	check_devided(t_map *map, int len, int i, int j)
{
	char	**arr;
	int		lent;

	arr = map->tab_map;
	lent = ft_strlen(arr[i]);
	if (i == len - 1 || ft_strlen(arr[i]) <= j || is_sp(arr[i], j))
	{
		printf("*The map must be closed by character '1'! \n");
		free_myallocation(map, 0);
		exit(EXIT_SUCCESS);
	}
	while (j && arr[i][j] == ' ')
		j--;
	j++;
	while (arr[i][j] && arr[i][j] == ' ')
	{
		lent = ft_strlen(arr[i + 1]);
		if (i < len && lent > j && arr[i + 1][j] == ' ')
		{
			check_devided(map, len, i + 1, j);
		}
		j++;
	}
}

void	check_firstlastline(t_map *map, char **arr, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (arr[i] && arr[i][++j])
		{
			if (!i || i == len -1)
			{
				if (arr[i][j] != '1' && arr[i][j] != '\n' && arr[i][j] != ' ')
					runerror(map, arr, i, j);
			}
			if (is_sp(arr[i], 0))
			{
				printf("Unbvalide Line in the map : %d! \n", i + 1);
				free_myallocation(map, 0);
				exit(EXIT_SUCCESS);
			}
			seconde_part(map, i, j);
		}
	}
}
