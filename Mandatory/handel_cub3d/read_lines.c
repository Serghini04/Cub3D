/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/15 18:11:20 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
		if (i < 6 && line[0] != '\n')
		{
			ft_check_line(line, index_line, map);
			i++;
		}
		else if (i >= 6 && line[0] != '\n' && !is_sp(line, 0))
		{
			map->tab_map[++j] = ft_strdup(line);
			i++;
		}
		else if (j >= 0 && i < len_map + 6 && (line[0] == '\n' || is_sp(line, 0)))
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
	lent = (int)ft_strlen(arr[i]);
	while (i <= len - 1 && lent > j && arr[i][j] == ' ')
	{
		if (i == len - 1 || (int)ft_strlen(arr[i]) <= j || is_sp(arr[i], j))
		{
				printf("The map must be closed by character '1'! \n");
				free_myallocation(map, 0);
				exit(EXIT_SUCCESS);
		}
		while(j && arr[i][j]== ' ')
			j--;
		j++;
		while (arr[i][j] && arr[i][j + 1] == ' ')
		{
			lent = (int)ft_strlen(arr[i + 1]);
			if (i + 1 < len && lent > j && arr[i + 1][j] == ' ')
			{
				check_devided(map, len, i + 1, j);
			}
			j++;
		}
		i++;
	}
}

int	chek_previews(char **arr, int i, int j)
{
	while (1)
	{
		if (i == 0)
			return (1);
		while (j && arr[i][j] == ' ')
			j--;
		j++;
		while (arr[i][j] && arr[i][j] == ' ')
		{
			if ((int)ft_strlen(arr[i - 1]) -1 < j || is_sp(&arr[i - 1][j], 0) || is_sp(arr[i - 1], j + 1))
				return (1);
			if (arr[i - 1][j] == ' ')
			{
				i = i - 1;
				break ;
			}
			j++;
		}
		if (arr[i][j] != ' ')
			break ;
	}
	return (0);
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
			if (arr[i][j] == ' ' && !is_sp(&arr[i][j], 0) && !is_sp(arr[i], j + 1) && i < len - 1)
			{
				if (((int)ft_strlen(arr[i + 1]) - 1 < j || is_sp(&arr[i + 1][j], 0)))
				{
					printf("The map must be closed by character '1'! \n");
					free_myallocation(map, 0);
					exit(EXIT_SUCCESS);
				}
				if (i < len - 1 && arr[i + 1][j] == ' ' && chek_previews(arr, i + 1, j))
				{
					check_devided(map, len, i + 1, j);
				}
			}
			if (i == len - 1 && arr[i][j] == ' ' && !is_sp(&arr[i][j], 0) && !is_sp(arr[i], j + 1))
			{
				if (arr[i-1][j]== ' ' && chek_previews(arr, i -1 , j))
				{
					printf("The map must be closed by character '1'! \n");
					free_myallocation(map, 0);
					exit(EXIT_SUCCESS);
					
				}
			}
		}
	}
}
