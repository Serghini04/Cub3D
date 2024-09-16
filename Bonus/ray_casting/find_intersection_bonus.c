/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:16:54 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:35 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

float	check_angle(float angle)
{
	float	valid_angle;

	valid_angle = fmod(angle, (2 * M_PI));
	if (valid_angle < 0)
		valid_angle = (2 * M_PI) + valid_angle;
	return (valid_angle);
}

t_ray	get_redirection_ray(float angle)
{
	t_ray	res;

	res.angle = check_angle(angle);
	res.is_down = (res.angle > 0 && res.angle < M_PI);
	res.is_up = !res.is_down;
	res.is_right = (res.angle < 0.5 * M_PI || res.angle > 1.5 * M_PI);
	res.is_left = !res.is_right;
	res.dir = -1;
	return (res);
}

t_vec	find_hor_intersection(t_ray	*res, t_data *data)
{
	t_vec	hor;
	t_vec	step;

	init_first_intersection_hor(data, &hor, &step, res);
	while (1)
	{
		if (is_door(hor.x, hor.y - (res->is_up == 1), data))
		{
			res->dir = 5;
			break ;
		}
		else if (is_wall(hor.x, hor.y - (res->is_up == 1), data, res))
			break ;
		else
		{
			hor.x += step.x;
			hor.y += step.y;
		}
	}
	return (hor);
}

t_vec	find_ver_intersection(t_ray *res, t_data *data)
{
	t_vec	ver;
	t_vec	step;

	init_first_intersection_ver(data, &ver, &step, res);
	while (1)
	{
		if (is_door(ver.x - (res->is_left == 1), ver.y, data))
		{
			res->dir = Door;
			break ;
		}
		else if (is_wall(ver.x - (res->is_left == 1), ver.y, data, res))
			break ;
		else
		{
			ver.x += step.x;
			ver.y += step.y;
		}
	}
	return (ver);
}
