/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:54:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/14 10:59:27 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

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

int	mouse(int x, int y, t_data *data)
{
	(void)y;
	if (!data->mouse_enable)
		return (0);
	if (x < W / 2)
		data->p.angle += -0.03;
	else if (x > W / 2)
		data->p.angle += 0.03;
	mlx_mouse_move(data->mlx_win, W / 2, H / 2);
	return (0);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	init_minimap(t_data *d, t_vec_int *start_draw, t_vec_int *player_pos)
{
	start_draw->x = max(0, floor(d->p.pos.x / CUBE_SIZE) - MINIMAP_SIZE / 2);
	start_draw->y = max(0, floor(d->p.pos.y / CUBE_SIZE) - MINIMAP_SIZE / 2);
	player_pos->x = ((int)(d->p.pos.x / CUBE_SIZE) - start_draw->x) * CUBE_SIZE;
	player_pos->y = ((int)(d->p.pos.y / CUBE_SIZE) - start_draw->y) * CUBE_SIZE;
}
