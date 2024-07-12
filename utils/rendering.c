/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/12 12:08:14 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	my_pixel_put(t_img *img, int x, int y, int color, t_data *data)
{
	int	pos;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	pos = (img->len * y) + (x * (img->bit_pixel / 8));
	*(int *)(img->p_pixel + pos) = color;
}

int get_color(t_data *data, int type, t_vec *pos)
{

	int of;

	of = ((int)data->tex[type].width *
						(int)pos->y + (int)pos->x);
	if ((int)pos->x >= 0 && (int)pos->x < data->tex[type].width &&
			(int)pos->y >= 0 && (int)pos->y < data->tex[type].height)
		return (*(data->tex[type].add + of));
	return (0);
}
	// float	distance_Projection;
	// float	wall_strip_height;
	// float	y;
	// float	top_wall;
	// float	bottom_wall;
	// distance_Projection = (data->width / 2) / tan(FOV / 2);
	// wall_strip_height = (CUBE_SIZE / (data->rays[i].distance * cos(data->rays[i].angle - data->p.angle))) * distance_Projection;

	// // find top & bottom6
	// top_wall = (data->height / 2) - (wall_strip_height / 2);
	// top_wall = top_wall < 0 ? 0 : top_wall;
	// bottom_wall = (data->height / 2) + (wall_strip_height / 2);
	// bottom_wall = bottom_wall > data->height ? data->height : bottom_wall;
	// y = top_wall;

void	render_3d(t_data *data)
{
	int		i;
	float	dist;
	t_vec	start;
	t_vec	index_img;
	float	wall_height;
	t_vec	tex;
	int		color;
	float	y;
	float	a = CUBE_SIZE;

	i = 0;
	fill_field_of_view(data);
	int index;
	while (i < data->num_rays)
	{
		int		color;
		t_vec	pos[3];
		float	dist_to_camera;
		float	wall_height;

		dist_to_camera = (data->width / 2) / tan(FOV / 2);
		wall_height = a * dist_to_camera / data->rays[i].distance;
		set_vec(&pos[0], data->width, data->height);
		set_vec(&pos[1], i,
			max(0, pos[0].y / 2 - wall_height / 2));
		pos[2].x = data->rays[i].is_ver ? (int)fmod(data->rays[i].to_hit_wall.y, a) / a * 64 : (int)fmod(data->rays[i].to_hit_wall.x, a) / a * 64;
		index = -1;
		while (++index < wall_height && ++pos[1].y < pos[0].y)
		{
			// restrain_pos(&pos[1], &pos[0]);
			pos[2].y = (pos[1].y - (pos[0].y / 2 - wall_height / 2))
				/ wall_height * 64;
			color = get_color(data, North, &pos[2]);
			if (color)
				my_pixel_put(&data->img, pos[1].x, pos[1].y, color, data);
		}
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
			my_pixel_put(&data->img, x + i, y + j, color, data);
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
			my_pixel_put(&data->img, p.x + i, p.y + j, color, data);
			j++;
		}
		i++;
	}
}

void	draw_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.angle - (FOV / 2);
	while (i < data->num_rays)
	{
		draw_line(data->rays[i].to_hit_wall.x * SIZE_MINI_MAP, data->rays[i].to_hit_wall.y * SIZE_MINI_MAP, data);
		ray_angle += FOV / data->num_rays;
		i++;
	}
}

void	rendering_minimap(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;

	while (i * CUBE_SIZE < data->height)
	{
		j = 0;
    	len = ft_strlen(data->map[i]);
		while (j < len)
		{
			int x = ceil((j * CUBE_SIZE) * SIZE_MINI_MAP);
			int y = ceil((i * CUBE_SIZE) * SIZE_MINI_MAP);
			int size = ceil(CUBE_SIZE * SIZE_MINI_MAP);
			if (data->map[i][j] == '1')
			    put_color(data, x, y, WHITE, size);
			else
			    put_color(data, x, y, BLACK, size);
			j++;
		}
		i++;
	}
	draw_player(data, RED, PLAYER_SIZE);
	draw_field_of_view(data);
}

void	clr_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			my_pixel_put(&data->img, j, i, BLACK, data);
			j++;
		}
		i++;
	}
}

int	start_rendering(t_data *data)
{
	render_3d(data);
	rendering_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	clr_window(data);
	return (0);
}
