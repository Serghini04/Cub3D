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

#include "../Cub3D.h"

float check_angle(float angle)
{
    float   valid_angle;

    valid_angle = fmod(angle, (2 * M_PI));
    if (valid_angle < 0) {
        valid_angle = (2 * M_PI) + valid_angle;
    }
    return (valid_angle);
}

float	distance_two_points(t_vec a, t_vec b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

t_ray	get_redirection_ray(float angle)
{
	t_ray	res;

    // the normalizeAngle function is used to keep the rayAngle within a predictable and standard range.
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

	// find first intercept:
	hor.y = floor(data->p.pos.y / CUBE_SIZE) * CUBE_SIZE;
	hor.y += (res.is_down == 1) * CUBE_SIZE;
	hor.x = data->p.pos.x + (hor.y - data->p.pos.y) / tan(res.angle);

	// Calculate the increment xstep and ystep
	step.y = CUBE_SIZE;
	if (res.is_up)
		step.y *= -1;
	step.x = step.y / tan(res.angle);
	if (res.is_left && step.x > 0)
		step.x *= -1;
	if (res.is_right && step.x < 0)
		step.x *= -1;
	while ((hor.x / CUBE_SIZE) >= 0 && (hor.x / CUBE_SIZE) <= data->width && (hor.y / CUBE_SIZE) >= 0 && (hor.y/ CUBE_SIZE) <= data->height)
	{
		if (is_wall(hor.x, hor.y - (res.is_up == 1), data))
			break;
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

		// find first intercept :
	ver.x = floor(data->p.pos.x / CUBE_SIZE) * CUBE_SIZE;
	ver.x += (res.is_right == 1) * CUBE_SIZE;
	ver.y = data->p.pos.y + (ver.x - data->p.pos.x) * tan(res.angle);

	step.x = CUBE_SIZE;
	step.x *= res.is_left ? -1 : 1;

	step.y = CUBE_SIZE * tan(res.angle);
	step.y *= (res.is_up && step.y > 0) ? -1 : 1;
	step.y *= (res.is_down && step.y < 0) ? -1 : 1;
	while ((ver.x / CUBE_SIZE) >= 0 && (ver.x / CUBE_SIZE) <= data->width && (ver.y / CUBE_SIZE) >= 0 && (ver.y/ CUBE_SIZE) <= data->height)
	{
		if (is_wall(ver.x - (res.is_left == 1), ver.y, data)) {
			break;
		}
		else
		{
			ver.x += step.x;
			ver.y += step.y;
		}
	}
	return (ver);
}

t_ray	ray_casting(float ray_angle, t_data *data)
{
	t_ray	res;
	float	horzdist;
	float	vertdist;
	t_vec	next_ver;
	t_vec	next_hor;

	// get rediraction :
	res = get_redirection_ray(ray_angle);
	next_hor = find_hor_intersection(res, data);
	// (the same).
	next_ver = find_ver_intersection(res, data);
	// cmp :
	horzdist = distance_two_points(data->p.pos, next_hor);
	vertdist = distance_two_points(data->p.pos, next_ver);
	if (vertdist < horzdist)
	{
		res.distance = vertdist * cos(res.angle - data->p.angle);
		res.to_hit_wall = next_ver;
		res.is_ver = 1;
	}
	else
	{
		res.distance = horzdist * cos(res.angle - data->p.angle);
		res.to_hit_wall = next_hor;
		res.is_ver = 0;
	}
	return (res);
}

void	fill_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.angle - (FOV / 2);
	while (i < data->num_rays)
	{
		data->rays[i] = ray_casting(ray_angle, data);
		ray_angle += FOV / data->num_rays;
		i++;
	}
}
