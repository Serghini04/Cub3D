/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:48 by hidriouc          #+#    #+#             */
/*   Updated: 2024/08/26 10:33:58 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	scap_spaces(const char *str, size_t *i, int *sign)
{
	while (str[*i] == 32 || (str[*i] <= 13 && str[*i] >= 9))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}
int	ft_atoi(const char *str)
{
	unsigned long	i_num;
	int				sign;
	size_t			i;

	i = 0;
	i_num = 0;
	sign = 1;
	if(!str || !*str)
	{
		return (-19);
	}
	scap_spaces(str, &i, &sign);
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
