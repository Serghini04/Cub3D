/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/18 14:06:37 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	init_game(t_data *data)
{
	init_textures(data);
	data->rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
		my_free(data);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	set_vec(t_vec *vec, float x, float y)
{
	vec->x = x;
	vec->y = y;
}

void	intro(void)
{
	printf("\033[94m    ____      _    _____ ____\n");
	printf("   / ___|   _| |__|___ /|  _ \\\n");
	printf("  | |  | | | | '_ \\ |_ \\| | | |\n");
	printf("  | |__| |_|");
	printf(" | |_) |__) | |_| |\n   \\___");
	printf("_\\__,_|_.__/____/|____/\n");
	printf("  👹Welcome, player! Let's start the game👹.\n");
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_map	map;

	if (ac != 2)
	{
		printf("Number of argummet not valid !!\n");
		return (1);
	}
	ft_handel_input(&map, &data, av);
	intro();
	start_init_mlx(&data);
	init_game(&data);
	mlx_loop_hook(data.mlx, loopfunc, &data);
	mlx_hook(data.mlx_win, 2, 1, onpress, &data);
	mlx_hook(data.mlx_win, 3, 2, onrelease, &data);
	mlx_hook(data.mlx_win, 17, 0, my_free, &data);
	mlx_loop(data.mlx);
	return (0);
}
