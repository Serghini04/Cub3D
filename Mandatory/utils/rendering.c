/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 18:13:46 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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

void	render_3d(t_data *data)
{
	t_vec	pos[2];
	float	wall_height;
	int		i;
	int		texture_height;
	int		index;

	i = 0;
	while (i < data->num_rays)
	{
		init_drawing_floor(data, i, pos, &wall_height);
		texture_height = data->tex[data->rays[i].dir].height;
		index = -1;
		while (++index < wall_height && ++pos[1].y < H)
		{
			pos[0].y = (pos[1].y - (H / 2 - wall_height / 2))
				/ wall_height * texture_height;
			my_pixel_put(&data->img, pos[1].x, pos[1].y, get_color(data, \
											data->rays[i].dir, &pos[0]));
		}
		while (pos[1].y++ < H)
			my_pixel_put(&data->img, i, pos[1].y, data->f);
		i++;
	}
}

void	clr_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height / CUBE_SIZE)
	{
		j = 0;
		while (j < data->width / CUBE_SIZE)
		{
			my_pixel_put(&data->img, j, i, BLACK);
			j++;
		}
		i++;
	}
}

int	start_rendering(t_data *data)
{
	fill_field_of_view(data);
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	clr_window(data);
	return (0);
}
