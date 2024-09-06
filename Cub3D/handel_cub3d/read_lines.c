/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdriouch <hdriouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:28:04 by hdriouch          #+#    #+#             */
/*   Updated: 2024/09/06 12:29:12 by hdriouch         ###   ########.fr       */
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
	index_line = 0;
	while ((line = get_next_line(fd)) && ++index_line)
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
		printf ("open() failed ! maby Pathfile_map {%s}not existed!\n", av[1]);
		free_arr(map->tab_map);
		exit(EXIT_FAILURE);
	}
	read_lines(map, fd, len_map);
	close(fd);
	return (len_map);
}

void	check_firstlastline(t_map *map,char **arr, int len)
{
	int i;
	int j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while(arr[i] && arr[i][j])
		{
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
			j++;
		}
		i += len - 1;
	}
}
