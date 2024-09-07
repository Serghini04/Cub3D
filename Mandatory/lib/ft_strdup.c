/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:00:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/17 21:43:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	*ft_strdup(char *s1)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = ((char *)s1)[i];
		i++;
	}
	((char *)res)[i] = '\0';
	return (res);
}
