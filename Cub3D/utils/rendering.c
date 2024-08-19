/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/08/19 11:32:02 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	render_3d(t_data *data)
{
	int		i;
	int		color;
	t_vec	pos[3];
	float	dist_to_camera;
	float	wall_height;
	int		index;

	i = 0;
	fill_field_of_view(data);
	while (i < data->num_rays)
	{

		dist_to_camera = (data->width / 2) / tan(FOV / 2);
		wall_height = (float)CUBE_SIZE * dist_to_camera / data->rays[i].distance;
		set_vec(&pos[0], W, H);
		set_vec(&pos[1], i, max(0, pos[0].y / 2 - wall_height / 2));
		pos[2].x = data->rays[i].is_ver ? (int)fmod(data->rays[i].to_hit_wall.y, (float)CUBE_SIZE) / (float)CUBE_SIZE * 64
		: (int)fmod(data->rays[i].to_hit_wall.x, (float)CUBE_SIZE) / (float)CUBE_SIZE * 64;
		index = -1;
		int y = 0;
		while (y++ < pos[1].y)
			my_pixel_put(&data->img, i, y, data->c);
		while (++index < wall_height && ++pos[1].y < pos[0].y)
		{
			pos[2].y = (pos[1].y - (pos[0].y / 2 - wall_height / 2))
				/ wall_height * 64;
			color = get_color(data, data->rays[i].dir, &pos[2]);
			if (color)
				my_pixel_put(&data->img, pos[1].x, pos[1].y, color);
		}
		while (pos[1].y++ < pos[0].y)
			my_pixel_put(&data->img, i, pos[1].y, data->f);
		i++;
	}
}

void	put_color(t_data *data, int x, int y, int color, int pow)
{
	int	i;
	int	j;

	i = 0;
	while (i < pow)
	{
		j = 0;
		while (j < pow)
		{
			my_pixel_put(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int color, int pow)
{
	int		i;
	int		j;
	t_vec	p;

	i = 0;
	p.x = data->p.pos.x * SIZE_MINI_MAP;
	p.y = data->p.pos.y * SIZE_MINI_MAP;
	while (i < pow)
	{
		j = 0;
		while (j < pow)
		{
			my_pixel_put(&data->img, p.x + i, p.y + j, color);
			j++;
		}
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
	render_3d(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	clr_window(data);
	return (0);
}
