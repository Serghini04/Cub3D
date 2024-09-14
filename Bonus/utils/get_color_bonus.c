/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:35:20 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/14 13:03:00 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

int	get_color(t_data *data, int type, t_vec *pos)
{
	int	of;

	of = ((int)data->tex[type].width * (int)pos->y + (int)pos->x);
	if ((int)pos->x >= 0 && (int)pos->x < data->tex[type].width && \
			(int)pos->y >= 0 && (int)pos->y < data->tex[type].height)
		return (*(data->tex[type].add + of));
	return (0);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	pos;

	if (x < 0 || y < 0 || x >= W || y >= H)
		return ;
	pos = (img->len * y) + (x * (img->bit_pixel / 8));
	*(int *)(img->p_pixel + pos) = color;
}
