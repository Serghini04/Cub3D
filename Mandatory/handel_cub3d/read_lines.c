/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/11 14:27:09 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	run_Error(t_map *map, int j)
{
	printf ("Empty line in the map !\n");
	free_myallocation(map, j + 1);
	exit(EXIT_SUCCESS);
}

void	read_lines(t_map *map, int fd, int len_map)
{
	char	*line;
	int		index_line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	index_line = 1;
	while ((line = get_next_line(fd)))
	{
		if (i < 6 && line[0] != '\n')
		{
			ft_check_line(line, index_line, map);
			i++;
		}
		else if (i >= 6 && line[0] != '\n')
		{
			map->tab_map[++j] = ft_strdup(line);
			i++;
		}
		else if (j >= 0 && i < len_map + 6 && line[0]== '\n')
			run_Error(map, j);
		free (line);
		++index_line;
	}
}

int	check_input(char **av, t_map *map)
{
	int	fd;
	int	len_map;

	check_namefile(av[1]);
	len_map = ft_allocmap(map, av);
	fd = open(av[1],  O_RDONLY , 0644);
	if (fd == -1)
	{
		printf ("open() failed ! maby Pathfile_map'%s' not existed!\n", av[1]);
		free_arr(map->tab_map);
		exit(EXIT_FAILURE);
	}
	read_lines(map, fd, len_map);
	close(fd);
	return (len_map);
}
int	ft_isaspaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
	}
	return (1);
	
}

void check_devided(t_map *map,int len, int i, int j)
{
	char **arr;

	arr = map->tab_map;
	if ( i == len - 1 || (int)ft_strlen(arr[i + 1]) - 2 < j)
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
			check_devided(map,len, i + 1, j);
		if (arr[i][j - 1] == ' ')
			j--;
		else
			break ;
	}
	return ;
}

void	check_firstlastline(t_map *map,char **arr, int len)
{
	int i;
	int j;
	int y;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (arr[i] && arr[i][++j])
		{
			y = i;
			if (arr[i][j] != '1' && arr[i][j] != '\n' && arr[i][j] != ' ')
			{
				if (is_player(arr[i][j]))
					printf("Invalid posotin of player !\n");
				else if (i)
					printf("Last line in the map is Invalid !\n");
				else
					printf("First line in the map is Invalid !\n");
				free_myallocation(map, 0);
				exit(EXIT_SUCCESS);
			}
			if (!i && arr[i][j] == ' ' && arr[i + 1])
				check_devided(map, len, i + 1, j);
			if (y >= len - 1 )
				{
					printf("The map must be closed by character '1'! \n");
					free_myallocation(map, 0);
					exit(EXIT_SUCCESS);
				}
			
			
		}
		i += len - 1;
	}
}
