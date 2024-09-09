/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_Cub3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:29:50 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/09 12:29:51 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	ft_check(t_map *map, char **arr, int i, int j)
{
	int flag;

	flag = 1;
	check_spand0(arr, &flag, i, j);
	check_player(arr, &flag, i, j);
	if (flag <= 0)
	{
		if (flag == -1)
			printf("Invalid position of player !\n");
		else
			printf ("Invalid map !!\n check line N: %d in the map\n", i + 1);
		free_myallocation(map, 0);
		exit(EXIT_SUCCESS);
	}

}

void	check_line(t_map *map, char **arr, int i, int j)
{
	while (arr[i][j])
	{
		if ((arr[i][j] != '1' && arr[i][j] != '\n' && arr[i][j] != ' ')\
		|| is_player(arr[i][j]))
		{
			if (is_player(arr[i][j]))
				printf("Invalid position of player !\n");
			else
				printf ("Invalid map !\nCheck line N : %d\n", i + 1);
			free_myallocation(map, 0);
			exit(EXIT_SUCCESS);
		}
		j++;
	}
}
void	check_arrmap(t_map *map, int len)
{
	int		i;
	int		j;
	char	*posnew_line;
	char	**arr;

	i = -1;
	arr = map->tab_map;
	check_firstlastline(map, arr, len);
	while (++i <= len - 1)
	{
		j = 0;
		posnew_line = ft_strchr(arr[i], '\n');
		if(posnew_line)
			*(--posnew_line) = '\0';
		while (arr[i][j] && arr[i +1] && arr[i + 1][j])
		{
			ft_check(map, arr, i, j);
			j++;
		}
		if (arr[i][j])
			check_line(map, arr, i, j);
		else if (arr[i + 1][j] )
			check_line(map, arr, i + 1, j);
	}

}

int	ft_handel_input(t_map *map, t_data *data, char **av)
{
	int	len_map;

	map->tex_so = NULL;
	map->tex_ea = NULL;
	map->tex_we = NULL;
	map->tex_no = NULL;
	len_map = check_input(av, map);
	check_arrmap(map, len_map);
	fill_data(map, data);
	return (1);
}
