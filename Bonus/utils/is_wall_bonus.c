/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:06:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 17:21:49 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

bool	is_valid_pos(int x, int y, t_data *data, char find)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (false);
	if ((int)ft_strlen(data->map[y]) < x)
		return (false);
	if (data->map[y][x] == find)
		return (true);
	return (false);
}

bool	is_wall(float x, float y, t_data *data, t_ray *res)
{
	int	new_x;
	int	new_y;

	(void)res;
	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D')
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1')
		return (true);
	return (false);
}

bool	is_wall2(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1' || \
	data->map[(int)floor(data->p.pos.y / CUBE_SIZE)][(int)floor(new_x)] == '1' \
	|| data->map[(int)floor(new_y)][(int)floor(data->p.pos.x / \
	CUBE_SIZE)] == '1')
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D')
		return (true);
	return (false);
}

bool	is_door(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (x < 0 || x > data->width || y < 0 || y > data->height)
		return (false);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
    	return (false);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D')
	{
		// printf("%d,%d\n", (int)floor(new_y), (int)floor(new_x));
		return (true);
	}
	return (false);
}
