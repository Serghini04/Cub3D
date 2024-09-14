/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/14 12:16:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D_bonus.h"

void	intro(void)
{
	printf("\033[94m   ____      _    _____ ____    ____\n");
	printf("  / ___|   _| |__|___ /|  _ \\  | __ )  ___  _ __  _   _ ___\n");
	printf(" | |  | | | | '_ \\ |_ \\| | | | |  _ \\ / _ \\| '_ \\| |");
	printf(" | / __|\n | |__| |_|");
	printf(" | |_) |__) | |_| | | |_) | (_) | | | | |_| \\__ \\\n  \\___");
	printf("_\\__,_|_.__/____/|____/  |____/ \\___/|_| |_|\\__,_|___/\n");
}

void	init_weapon(t_data *data)
{
	int		i;
	int		x;
	int		y;
	char	*name;
	char	*tmp;

	i = 0;
	tmp = NULL;
	name = NULL;
	while (i < 42)
	{
		tmp = ft_strjoin(ft_itoa(i), ".xpm");
		if (!tmp)
			(printf("malloc failing.\n"), exit(1));
		name = ft_strjoin("textures/cs2/", tmp);
		if (!name)
			(printf("malloc failing.\n"), exit(1));
		printf("Loading Texture : %s ✅, Please Wait...\n", name);
		data->weapon[i] = mlx_xpm_file_to_image(data->mlx, name, &x, &y);
		if (!data->weapon[i])
			(printf("Issue in converting image : %s\n", name), exit(1));
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
	system("clear");
	intro();
	printf("  👹Welcome, player! Let's start the game👹.\n");
	init_textures(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	if (ac != 2)
	{
		printf("Number of argummet not valid !!\n");
		return (1);
	}
	intro();
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
