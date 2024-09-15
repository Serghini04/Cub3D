/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/14 15:28:22 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	run_error(t_map *map, char *line, int j)
{
	if (is_sp(line))
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
		if (i < 6 && line[0] != '\n')
		{
			ft_check_line(line, index_line, map);
			i++;
		}
		else if (i >= 6 && line[0] != '\n' && !is_sp(line))
		{
			map->tab_map[++j] = ft_strdup(line);
			i++;
		}
		else if (j >= 0 && i < len_map + 6 && (line[0] == '\n' || is_sp(line)))
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

	arr = map->tab_map;
	if (i == len - 1 || (int)ft_strlen(arr[i + 1]) - 2 < j)
	{
		printf("The map must be closed by character '1'! \n");
		free_myallocation(map, 0);
		exit(EXIT_SUCCESS);
	}
	while (arr[i][j] && arr[i][j] == ' ')
		j++;
	--j;
	while (j >= 0 && arr[i][j] == ' ')
	{
		if (arr[i + 1] && arr[i + 1][j] == ' ')
			check_devided(map, len, i + 1, j);
		if (arr[i][j - 1] == ' ')
			j--;
		else
			break ;
	}
	return ;
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
			// if (arr[i][j] == ' ')
			// {
			// 	if (chek_alllines(arr, i, j, len))
					check_devided(map, len, i + 1, j);
			}
		}
	}
}
