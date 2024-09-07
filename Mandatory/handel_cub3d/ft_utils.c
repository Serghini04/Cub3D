/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:49:16 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/07 11:49:23 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_avalidchar(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '\n')
		return (1);
	return (0);
}

void	free_myallocation(t_map *map, int index)
{
	char	**arr;
	int		i;

	i = -1;
	arr = map->tab_map;
	free(map->tex_no);
	map->tex_no = NULL;
	free(map->tex_so);
	map->tex_so = NULL;
	free(map->tex_we);
	map->tex_we = NULL;
	free(map->tex_ea);
	map->tex_ea = NULL;
	if (index > 0)
	{
		while (++i < index && arr[i])
		free(arr[i]);
	}
	else if (!index)
		while (arr[++i])
			free(arr[i]);
	free(arr);
	map->tab_map = NULL;
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	check_namefile(char *name_map)
{
	int	i;

	i = 0;
	while (name_map[i])
		i++;
	if (ft_strncmp(&name_map[i - 4], ".cub", 4))
	{
		printf("Name of file_map Unvalide!\n");
		printf("EXE : PATH/filename.cub\n");
		exit(EXIT_FAILURE);
	}
}

int check_beginning(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	else if (!ft_strncmp(line, "SO ", 3))
		return (2);
	else if (!ft_strncmp(line, "WE ", 3))
		return (3);
	else if (!ft_strncmp(line, "EA ", 3))
		return (4);
	else if (!ft_strncmp(line, "C ", 2))
		return (5);
	else if (!ft_strncmp(line, "F ", 2))
		return (6);
	return (0); 
}
