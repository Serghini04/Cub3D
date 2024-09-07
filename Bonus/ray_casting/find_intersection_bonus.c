/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersection_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:16:54 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/17 21:16:57 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

//=>The normalizeAngle function is used to keep the rayAngle within
// a predictable and standard range.
float	check_angle(float angle)
{
	float	valid_angle;

	valid_angle = fmod(angle, (2 * M_PI));
	if (valid_angle < 0)
		valid_angle = (2 * M_PI) + valid_angle;
	return (valid_angle);
}

float	distance_two_points(t_vec a, t_vec b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_ray	get_redirection_ray(float angle)
{
	t_ray	res;

	res.angle = check_angle(angle);
	res.is_down = (res.angle > 0 && res.angle < M_PI);
	res.is_up = !res.is_down;
	res.is_right = (res.angle < 0.5 * M_PI || res.angle > 1.5 * M_PI);
	res.is_left = !res.is_right;
	return (res);
}

t_vec	find_hor_intersection(t_ray	res, t_data *data)
{
	t_vec	hor;
	t_vec	step;

	hor.y = floor(data->p.pos.y / CUBE_SIZE) * CUBE_SIZE;
	hor.y += (res.is_down == 1) * CUBE_SIZE;
	hor.x = data->p.pos.x + (hor.y - data->p.pos.y) / tan(res.angle);
	step.y = CUBE_SIZE;
	if (res.is_up)
		step.y *= -1;
	step.x = step.y / tan(res.angle);
	if (res.is_left && step.x > 0)
		step.x *= -1;
	if (res.is_right && step.x < 0)
		step.x *= -1;
	while (1)
	{
		if (is_wall(hor.x, hor.y - (res.is_up == 1), data))
			break ;
		else
		{
			hor.x += step.x;
			hor.y += step.y;
		}
	}
	return (hor);
}

t_vec	find_ver_intersection(t_ray res, t_data *data)
{
	t_vec	ver;
	t_vec	step;

	ver.x = floor(data->p.pos.x / CUBE_SIZE) * CUBE_SIZE;
	ver.x += (res.is_right == 1) * CUBE_SIZE;
	ver.y = data->p.pos.y + (ver.x - data->p.pos.x) * tan(res.angle);
	step.x = CUBE_SIZE;
	if (res.is_left)
		step.x *= -1;
	step.y = CUBE_SIZE * tan(res.angle);
	if (res.is_up && step.y > 0)
		step.y *= -1;
	if (res.is_down && step.y < 0)
		step.y *= -1;
	while (1)
	{
		if (is_wall(ver.x - (res.is_left == 1), ver.y, data))
			break ;
		else
		{
			ver.x += step.x;
			ver.y += step.y;
		}
	}
	return (ver);
}
