/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spand0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:55 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/07 11:48:57 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	check_spand0(char **arr, int *flag, int i, int j)
{
	if ((arr[i][j] == '0' && ( arr[i + 1][j] == ' ' ||\
		arr[i][j + 1] == ' ' || arr[i][j + 1] == '\0')) || arr[i][0] == '0')
		*flag = 0;
	else if (arr[i][j] == ' ' && (arr[i + 1][j] == '0' ||\
		arr[i][j + 1] == '0' || arr[i][j + 1] == 'D' || is_player(arr[i + 1][j])))
	{
		if (is_player(arr[i + 1][j]))
			*flag = -1;
		else if (arr[i][j] == 'D')
			*flag = -2;
		else
			*flag = 0;
	}
	else if ((arr[i][j] == 'D' &&  ( arr[i + 1][j] == ' ' ||\
		arr[i][j + 1] == ' ' || arr[i][j + 1] == '\0')) || arr[i][0] == 'D')
		*flag = -2;
}

void	check_player(char **arr, int *flag, int i, int j)
{
	if (is_player(arr[i][j]) && (j == 0 || arr[i][j + 1] == ' ' ||\
		arr[i + 1][j] == ' ' || arr[i][j + 1] == '\0'))
		*flag = -1;
	else if ((is_player(arr[i][j + 1])) && (arr[i][j] == ' ' ||\
		arr[i + 1][j + 1] == ' '))
		*flag = -1;
}