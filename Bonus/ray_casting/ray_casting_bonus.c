/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:33:50 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/12 11:33:50 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

t_ray	side_of_ray(t_ray res)
{
	if (res.dir == 5)
		res.dir = Door;
	if (res.dir == 4)
		return (res);
	if (res.is_down && !res.is_ver)
		res.dir = South;
	else if (res.is_up && !res.is_ver)
		res.dir = North;
	else if (res.is_left && res.is_ver)
		res.dir = West;
	else
		res.dir = East;
	return (res);
}

void	get_younger_ray(t_data *data, t_vec next_ver, t_vec next_hor, \
															t_ray *res)
{
	float	horzdist;
	float	vertdist;

	horzdist = distance_two_points(data->p.pos, next_hor);
	vertdist = distance_two_points(data->p.pos, next_ver);
	if (vertdist < horzdist)
	{
		res->distance = vertdist * cos(res->angle - data->p.angle);
		(1) && (res->to_hit_wall = next_ver, res->is_ver = 1);
		res->dir = res->door_ver;
	}
	else
	{
		res->distance = horzdist * cos(res->angle - data->p.angle);
		(1) && (res->to_hit_wall = next_hor, res->is_ver = 0);
		res->dir = res->door_hor;
	}
}

t_ray	ray_casting(float ray_angle, t_data *data)
{
	t_ray	res;
	t_vec	next_ver;
	t_vec	next_hor;

	res = get_redirection_ray(ray_angle);
	next_ver = find_ver_intersection(&res, data);
	next_hor = find_hor_intersection(&res, data);
	get_younger_ray(data, next_ver, next_hor, &res);
	return (side_of_ray(res));
}

void	fill_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	ray_angle = data->p.angle - (FOV / 2);
	while (i < data->num_rays)
	{
		data->rays[i] = ray_casting(ray_angle, data);
		ray_angle += FOV / data->num_rays;
		i++;
	}
}
