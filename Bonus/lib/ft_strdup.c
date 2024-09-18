/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:00:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/18 12:14:54 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

char	*stor_line(t_map *map, char *line)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (!tmp)
	{
		printf ("malloc failed !\n");
		free_myallocation(map, 0);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

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
