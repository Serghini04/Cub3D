/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handelline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdriouch <hdriouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:23:40 by hdriouch          #+#    #+#             */
/*   Updated: 2024/09/06 14:30:39 by hdriouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_checknext(t_map *map, char *line, int ret, int index_line)
{
	if (ret == 2)
	{
		map->tex_so = ft_strdup(line);
		if (!map->tex_so)
		return (0);  
	}
	else if (ret == 3)
	{
		map->tex_we = ft_strdup(line);
		if (!map->tex_we)
			return (0);  
	}
	else if (ret == 4)
	{
		map->tex_ea = ft_strdup(line);
		if (!map->tex_ea)
			return (0);  
	}
	else
		check_colloers(line, map, ret, index_line);
	return (1);
}
int ft_stor_line(char *line, t_map *map, int ret, int index_line)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (tmp)
		*(--tmp) = '\0';
	if (ret == 1)
	{
		map->tex_no = ft_strdup(line);
		if (!map->tex_no)
			return (0);
	}
	else if (!ft_checknext(map, line, ret, index_line))
			return (0);
	return (1);
}

void ft_check_line(char *line, int index_line, t_map *map)
{
	int i;
	int ret;

	i = 2;
	ret = check_beginning(line);
	while (line && line[i] && line[i] == ' ')
		i++;
	if (!ft_stor_line(&line[i], map, ret, index_line))
	{
		printf ("malloc failed !!\n");
		free_myallocation(map, -1);
		exit(EXIT_FAILURE);
	}
}

void	check_linemap(t_map *map, char *line, int index_line, int *flag)
{
	int i;
	static int	line_y;

	i = -1;
	line_y++;
	while (line && line[++i])
	{
		if (is_player(line[i]) && !*flag)
		{
			map->angle_view = line[i];
			map->pos_x = i;
			map->pos_y = line_y - 1;
			*flag = 1;
		}
		else if (is_player(line[i]) && *flag)
		{
			printf ("At least one player must exist in the map\n");
			exit(EXIT_SUCCESS);
		}
		if (!is_player(line[i]) && !is_avalidchar(line[i]))
		{
			printf("Invalide character in the map line : %d\n", index_line);
			exit(EXIT_SUCCESS);
		}
	}
}
