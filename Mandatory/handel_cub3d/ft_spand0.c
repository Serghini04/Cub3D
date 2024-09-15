/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spand0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:55 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/15 18:19:20 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_sp(char *line, int index)
{
	int	i;

	i = 0;
if (index)
{
	while (line && line[i] && line[i] != '\n' && i < index)
	{
		if (line[i] != ' ')
			return (0);
			i++;
	}
}
else
{
	while (line && line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
			i++;
	}

}
	return (1);
}

void	check_spand0(char **arr, int *flag, int i, int j)
{
	if ((arr[i][j] == '0' && ((int)ft_strlen(arr[i + 1]) - 1 <= j|| arr[i + 1][j] == ' ' || \
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
	if (is_player(arr[i][j]) && ((int)ft_strlen(arr[i + 1]) - 1 <= j || j == 0 || arr[i][j + 1] == ' ' || \
		arr[i + 1][j] == ' ' || arr[i][j + 1] == '\0'))
		*flag = -1;
	else if ((is_player(arr[i][j + 1])) && (arr[i][j] == ' ' || \
		arr[i + 1][j + 1] == ' '))
		*flag = -1;
}
