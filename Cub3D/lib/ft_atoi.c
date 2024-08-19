/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:48 by hidriouc          #+#    #+#             */
/*   Updated: 2024/08/17 13:16:06 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_atoi(const char *str)
{
	unsigned long	i_num;
	int				sign;
	size_t			i;

	i = 0;
	i_num = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (i_num > LONG_MAX / 10 && sign == 1)
			return (-1);
		if (i_num > LONG_MAX / 10 && sign == -1)
			return (0);
		i_num = (i_num * 10) + (str[i] - '0');
		i++;
	}
	return (((int)i_num) * sign);
}
