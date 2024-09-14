/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:04:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/14 11:45:58 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	init_drawing_floor(t_data *data, int i, t_vec *pos, float *wall_height)
{
	int		start;
	float	dist_to_wall;
	int		texture_width;

	texture_width = data->tex[data->rays[i].dir].width;
	dist_to_wall = (data->width / 2) / tan(FOV / 2);
	*wall_height = (float)CUBE_SIZE * dist_to_wall / data->rays[i].distance;
	set_vec(&pos[1], i, max(0, H / 2 - *wall_height / 2));
	if (data->rays[i].is_ver)
	{
		pos[0].x = fmod(data->rays[i].to_hit_wall.y, (float)CUBE_SIZE) \
											/ CUBE_SIZE * texture_width;
	}
	else
	{
		pos[0].x = fmod(data->rays[i].to_hit_wall.x, (float)CUBE_SIZE) \
											/ CUBE_SIZE * texture_width;
	}
	start = 0;
	while (start++ < pos[1].y)
		my_pixel_put(&data->img, i, start, data->c);
}

void	draw_player(t_data *data, int color, int player_x, int player_y)
{
	int		i;
	int		j;
	t_vec	p;

	i = 0;
	p.x = player_x + (CUBE_SIZE / 2);
	p.y = player_y + (CUBE_SIZE / 2);
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			my_pixel_put(&data->img, p.x + i, p.y + j, color);
			j++;
		}
		i++;
	}
}

void	put_color(t_data *data, t_vec_int pos, int color, int pow)
{
	int	i;
	int	j;

	i = 0;
	while (i < pow)
	{
		j = 0;
		while (j < pow)
		{
			my_pixel_put(&data->img, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

t_vec_int	set_vec_int(t_vec_int data, int x, int y)
{
	data.x = x;
	data.y = y;
	return (data);
}
