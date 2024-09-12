/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/12 18:13:18 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

void	init_weapon(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < 42)
	{
		char *res= ft_strjoin("textures/cs2/", ft_strjoin(ft_itoa(i), ".xpm"));
		if (!res)
		{
			printf("Malloc failing !!!\n");
			exit(1);
		}
		data->weapon[i] = mlx_xpm_file_to_image(data->mlx, res, &x, &y);
		if (!data->weapon[i])
		{
			printf("Issue in converting image : %s\n", res);
			exit(1);
		}
		i++;
	}
}

void	init_game(t_data *data)
{
	init_weapon(data);
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

void	f(void)
{
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	int  i;

	i = 0;
	// atexit(f);
	if (ac != 2)
	{
		printf("Number of argummet not valid !!\n");
		return (1);
	}
	ft_handel_input(&map, &data, av);
	start_init_mlx(&data);
	init_game(&data);
	mlx_mouse_move(data.mlx_win, 0, 0);
	mlx_hook(data.mlx_win, 6, 0, mouse, &data);
	mlx_loop_hook(data.mlx, loopfunc, &data);
	mlx_hook(data.mlx_win, 2, 1, onpress, &data);
	mlx_hook(data.mlx_win, 3, 2, onrelease, &data);
	mlx_loop(data.mlx);
	return (0);
}
