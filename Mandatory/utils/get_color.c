/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:54:16 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/17 14:01:50 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
