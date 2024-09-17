/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:50:00 by hidriouc          #+#    #+#             */
/*   Updated: 2024/09/17 12:32:30 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			i++;
			return (&s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*found_line(int fd, char **s_ptr)
{
	char	*ln;
	char	*p_of_buffer;
	char	*tmp;
	ssize_t	index;

	index = 1;
	p_of_buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!p_of_buffer)
		return (free(*s_ptr), *s_ptr = NULL, NULL);
	while (index > 0)
	{
		index = read(fd, p_of_buffer, BUFFER_SIZE);
		if (index == -1)
			break ;
		p_of_buffer[index] = '\0';
		*s_ptr = str_join(*s_ptr, p_of_buffer);
		if (ft_strchr(*s_ptr, '\n') || !*s_ptr)
		{
			ln = premier_ligne(*s_ptr);
			tmp = *s_ptr;
			*s_ptr = str_dup(str_chr(*s_ptr, '\n'));
			return ((free(p_of_buffer), free(tmp)), ln);
		}
	}
	return (free(p_of_buffer), p_of_buffer = NULL, NULL);
}

char	*premier_ligne(char *ptr_of_bfr1)
{
	char	*line;
	size_t	len;
	size_t	i;

	i = 0;
	if (!ptr_of_bfr1 || !*ptr_of_bfr1)
		return (NULL);
	len = str_len(ptr_of_bfr1, '\n');
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (ptr_of_bfr1[i])
	{
		line[i] = ptr_of_bfr1[i];
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s_ptr;
	char		*l_ne;
	char		*tmp;

	tmp = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		if (s_ptr)
		{
			free(s_ptr);
			s_ptr = NULL;
		}
		return (NULL);
	}
	l_ne = found_line(fd, &s_ptr);
	if (!l_ne && s_ptr)
	{
		tmp = s_ptr;
		l_ne = premier_ligne(s_ptr);
		s_ptr = str_dup(str_chr(s_ptr, '\n'));
		(free(tmp), tmp = NULL);
	}
	return (l_ne);
}
