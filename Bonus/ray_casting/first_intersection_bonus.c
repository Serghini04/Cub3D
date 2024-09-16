/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_intersection_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:18:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 17:20:02 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	init_first_intersection_ver(t_data *data, t_vec *ver, t_vec *step, \
																	t_ray *res)
{
	ver->x = floor(data->p.pos.x / CUBE_SIZE) * CUBE_SIZE;
	ver->x += (res->is_right == 1) * CUBE_SIZE;
	ver->y = data->p.pos.y + (ver->x - data->p.pos.x) * tan(res->angle);
	step->x = CUBE_SIZE;
	if (res->is_left)
		step->x *= -1;
	step->y = CUBE_SIZE * tan(res->angle);
	if (res->is_up && step->y > 0)
		step->y *= -1;
	if (res->is_down && step->y < 0)
		step->y *= -1;
}

void	init_first_intersection_hor(t_data *data, t_vec *hor, t_vec *step, \
																	t_ray *res)
{
	hor->y = floor(data->p.pos.y / CUBE_SIZE) * CUBE_SIZE;
	hor->y += (res->is_down == 1) * CUBE_SIZE;
	hor->x = data->p.pos.x + (hor->y - data->p.pos.y) / tan(res->angle);
	step->y = CUBE_SIZE;
	if (res->is_up)
		step->y *= -1;
	step->x = step->y / tan(res->angle);
	if (res->is_left && step->x > 0)
		step->x *= -1;
	if (res->is_right && step->x < 0)
		step->x *= -1;
}
