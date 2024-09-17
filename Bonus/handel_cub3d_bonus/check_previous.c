/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_previous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:32:46 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/17 13:59:58 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

int	check_previous(char **arr, int i, int j)
{
	while (1)
	{
		if (i == 0 || ft_str_len(arr[i]) - 1 < j)
			return (1);
		while (j && arr[i][j] == ' ')
			j--;
		j++;
		while (arr[i][j] && arr[i][j] == ' ')
		{
			if (ft_str_len(arr[i - 1]) - 1 < j || is_sp(&arr[i - 1][j], 0) || \
				is_sp(arr[i - 1], j + 1))
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

void	ft_second(t_map *map, char **arr, int i, int j)
{
	if (ft_str_len(arr[i - 1]) - 1 > j && arr[i - 1][j] == ' ' && \
			check_previous(arr, i - 1, j))
	{
		printf("The map must be closed by character '1'! \n");
		free_myallocation(map, 0);
		exit(EXIT_SUCCESS);
	}
}

void	seconde_part(t_map *map, int i, int j)
{
	int		len;
	char	**arr;

	len = map->len;
	arr = map->tab_map;
	if (arr[i][j] == ' ' && !is_sp(&arr[i][j], 0) && \
		!is_sp(arr[i], j + 1) && i < len - 1)
	{
		if ((ft_str_len(arr[i + 1]) - 1 < j || \
			is_sp(&arr[i + 1][j], 0)) && check_previous(arr, i, j))
		{
			printf("The map must be closed by character '1'! \n");
			free_myallocation(map, 0);
			exit(EXIT_SUCCESS);
		}
		if (ft_str_len(arr[i + 1]) - 1 > j && arr[i + 1][j] == ' '\
			&& check_previous(arr, i, j))
		{
			check_devided(map, len, i + 1, j);
		}
	}
	if (i == len - 1 && arr[i][j] == ' ' && !is_sp(&arr[i][j], 0) && \
		!is_sp(arr[i], j + 1))
		ft_second(map, arr, i, j);
}
