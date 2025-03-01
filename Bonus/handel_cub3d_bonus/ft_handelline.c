/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handelline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:31 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/18 13:38:38 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	check_door(char **arr, int *flag, int i, int j)
{
	if (arr[i][j] == 'D' && (!i || !j || !arr[i][j + 1] || \
		((arr[i][j + 1] != '1' || arr[i][j - 1] != '1' ) && \
			(arr[i + 1][j] != '1' || arr[i - 1][j] != '1'))))
		*flag = -2;
}

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

int	ft_stor_line(char *line, t_map *map, int ret, int index_line)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (tmp)
		*(--tmp) = '\0';
	if (!line[0])
	{
		printf("Unvalid Line : %d\n", index_line);
		free_myallocation(map, -1);
		exit(EXIT_FAILURE);
	}
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

void	ft_check_line(char *line, int index_line, t_map *map)
{
	int	i;
	int	ret;

	i = 2;
	ret = check_beginning(line);
	if (!ret)
	{
		printf("Unvalid Input in the line : %d \n", index_line);
		printf("OR Missing some elemments of input file\n");
		free_myallocation(map, -1);
		exit(EXIT_FAILURE);
	}
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
	int			i;
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
			printf("Unvalid Line in the map line : %d\n", index_line);
			exit(EXIT_SUCCESS);
		}
	}
}
