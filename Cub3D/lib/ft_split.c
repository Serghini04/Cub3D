/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:49:51 by hidriouc          #+#    #+#             */
/*   Updated: 2024/08/17 12:26:31 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

static size_t	c_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static char	*cr_string(const char *p, char c)
{
	size_t	i;
	char	*p1;

	i = 0;
	while (p[i] && p[i] != c)
		i++;
	p1 = (char *)malloc((i + 1) * sizeof (char));
	if (!p1)
		return (NULL);
	i = 0;
	while (*p && *p != c)
	{
		p1[i] = *p;
		i++;
		p++;
	}
	p1[i] = 0;
	return (p1);
}

static void	free_all(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
	{
		free (p[i]);
		i++;
	}
	free(p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	p = (char **)malloc((c_word(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			p[i] = cr_string(s, c);
			if (!p[i])
				return (free_all(p), NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	return (p[i] = NULL, p);
}
