/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:49:38 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/07 11:49:45 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

size_t	str_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

void	*mem_cpy(void *dst, void *src, size_t n)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		i++;
	}
	((unsigned char *)dst)[i] = '\0';
	return (ptr);
}

char	*str_chr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c && s[i + 1])
		{
			i++;
			return (&s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*str_dup(char *s1)
{
	char	*p;
	size_t	i;

	i = str_len(s1, '\0');
	if (!s1 || !*s1)
		return (NULL);
	p = (char *)malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	mem_cpy(p, s1, i);
	return (p);
}

char	*str_join(char *s1, char *s2)
{
	char	*p;
	size_t	size;
	size_t	size1;
	size_t	size2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size1 = str_len(s1, '\0');
	size2 = str_len(s2, '\0');
	size = size1 + size2;
	p = (char *)malloc((size + 1) * sizeof(char));
	if (!p)
		return (free(s1), s1 = NULL, NULL);
	mem_cpy(p, s1, size1);
	mem_cpy(p + size1, s2, size2);
	free(s1);
	s1 = NULL;
	return (p);
}
