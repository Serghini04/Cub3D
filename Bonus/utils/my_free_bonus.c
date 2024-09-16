/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:24:55 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 18:05:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

int	my_free(t_data *data)
{
	int	i;

	i = 0;
	free_arr(data->map);
	while (i < 5)
	{
		free(data->tex[i].add);
		i++;
	}
	free(data->tex);
	if (data->rays)
		free(data->rays);
	mlx_destroy_image(data->mlx, data->img.p_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(1);
}
