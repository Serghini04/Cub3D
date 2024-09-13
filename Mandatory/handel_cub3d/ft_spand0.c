/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spand0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:55 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/13 15:37:35 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_sp(char *line)
{
	int	i;

	i = -1;
	while (line && line[++i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
	}
	return (1);
}

void	check_spand0(char **arr, int *flag, int i, int j)
{
	if ((arr[i][j] == '0' && (arr[i + 1][j] == ' ' || \
		arr[i][j + 1] == ' ' || arr[i][j + 1] == '\0')) || arr[i][0] == '0')
		*flag = 0;
	else if (arr[i][j] == ' ' && (arr[i + 1][j] == '0' || \
		arr[i][j + 1] == '0' || is_player(arr[i + 1][j])))
	{
		if (is_player(arr[i + 1][j]))
			*flag = -1;
		else if (arr[i][j] == 'D')
			*flag = -2;
		else
			*flag = 0;
	}
}

void	check_player(char **arr, int *flag, int i, int j)
{
	if (is_player(arr[i][j]) && (j == 0 || arr[i][j + 1] == ' ' || \
		arr[i + 1][j] == ' ' || arr[i][j + 1] == '\0'))
		*flag = -1;
	else if ((is_player(arr[i][j + 1])) && (arr[i][j] == ' ' || \
		arr[i + 1][j + 1] == ' '))
		*flag = -1;
}
