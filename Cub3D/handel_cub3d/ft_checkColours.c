/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkColours.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdriouch <hdriouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:11:24 by hdriouch          #+#    #+#             */
/*   Updated: 2024/09/06 11:20:27 by hdriouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_check_maxcollor(int R, int G, int B)
{
	if (R > 255 || R < 0 || G > 255 || G < 0 ||  B > 255 || B < 0)
		return (1);
	return (0);
}

void	check_syntax(t_map *map, char *line, int index_line)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ',')
			counter++;
		if ((!(line[i] >= '0' && line[i] <= '9') && line[i] != ',') || counter > 2)
		{
			printf ("Error: \nInvalid Syntax in the line %d\n", index_line);
			printf ("EXE : (F or C) 255,255,255\n");
			free_myallocation(map, -1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int chift_coolor(unsigned int R, unsigned int G, unsigned int B)
{
	return (R << 24 | G << 16 | B << 8 | (unsigned int)255);
}
void	is_validRGB(t_map *map, int index_line, char **ptr)
{
		if (!ptr || !*ptr || !*(ptr + 1) || !*(ptr + 2))
	{
		free_arr(ptr);
		free_myallocation(map, -1);
		printf ("Unvalide line : %d\n", index_line);
		printf ("EXE :(F or C) 255,255,255\n");
		exit(EXIT_FAILURE);
	}
	else if (ptr[0][0] == '\n' || ptr[1][0] == '\n' || ptr[2][0] == '\n')
	{
		free_arr(ptr);
		free_myallocation(map, -1);
		printf ("Unvalide line : %d\n", index_line);
		printf ("EXE :(F or C) 255,255,255\n");
		exit(EXIT_FAILURE);
	}
}
void	check_colloers(char *line, t_map *map, int ret, int index_line)
{
	char			**ptr;
	unsigned int	R;
	unsigned int	G;
	unsigned int	B;

	ptr = NULL;
	check_syntax(map, line, index_line);
	ptr = ft_split(line, ',');
	is_validRGB(map, index_line, ptr);
	R = ft_atoi(ptr[0]);
	G = ft_atoi(ptr[1]);
	B = ft_atoi(ptr[2]);
	if (ft_check_maxcollor(R, G, B))
	{
		free_arr(ptr);
		free_myallocation(map, -1);
		printf ("There are no colours that match your input ");
		printf("RGB in line : %d\n", index_line);
		exit(EXIT_FAILURE);
	}
	if (ret == 5)
		map->ceil = chift_coolor(R, G, B);
	else if (ret == 6)
		map->floor = chift_coolor(R, G, B);
	free_arr(ptr);
}
