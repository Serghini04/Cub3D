/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:07:12 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/17 14:51:08 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	my_free(t_data *data)
{
	int	i;

	i = 0;
	free_arr(data->map);
	while (i < 4)
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
