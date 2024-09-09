/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/07 16:53:06 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	init_game(t_data *data)
{
	data->rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(1);
	}
	init_textures(data);
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

void f()
{
	system("leaks cub3D");
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_map	map;

	// atexit(f);
	if (ac != 2)
	{
		printf("Number of argummet not valid !!\n");
		return (1);
	}
	ft_handel_input(&map, &data, av);
	start_init_mlx(&data);
	init_game(&data);
	mlx_loop_hook(data.mlx, loopfunc, &data);
	mlx_hook(data.mlx_win, 2, 1, onpress, &data);
	mlx_hook(data.mlx_win, 3, 2, onrelease, &data);
	mlx_loop(data.mlx);
	return (0);
}
