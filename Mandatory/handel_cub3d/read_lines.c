/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/13 11:19:06 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	run_Error(t_map *map, char *line, int j)
{
	if (is_spaces(line))
		printf ("The map must be closed by character '1'! \n");
	else
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
		else if (i >= 6 && line[0] != '\n' && !is_spaces(line))
		{
			map->tab_map[++j] = ft_strdup(line);
			i++;
		}
		else if (j >= 0 && i < len_map + 6 && (line[0]== '\n' || is_spaces(line)))
			run_Error(map,line, j);
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
		free(map->tab_map);
		exit(EXIT_FAILURE);
	}
	read_lines(map, fd, len_map);
	close(fd);
	return (len_map);
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
void	runError(t_map *map, char **arr, int i, int j)
{
		if (is_player(arr[i][j]))
			printf("Unvalid posotin of player !\n");
		else if (i)
			printf("Last line in the map is Invalid !\n");
		else
			printf("First line in the map is Invalid !\n");
		free_myallocation(map, 0);
		exit(EXIT_SUCCESS);
}
int chek_alllines(char **arr, int i, int j, int len)
{
	while(i < len )
	{
		if ((int)ft_strlen(arr[i]) > j && !is_spaces(&arr[i][j]))
			return (1);
		i++;
	}
	return(0);
}
void	check_firstlastline(t_map *map,char **arr, int len)
{
	int i;
	int j;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (arr[i] && arr[i][++j])
		{
			if (!i || i == len -1)
			{
				if (arr[i][j] != '1' && arr[i][j] != '\n' && arr[i][j] != ' ')
					runError(map, arr, i, j);
				
			}
			if (arr[i][j] == ' ')
			{
				if (chek_alllines(arr, i, j, len))
					check_devided(map, len, i + 1, j);
			}
		}
	}
}
