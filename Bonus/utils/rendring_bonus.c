/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/14 12:06:46 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

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

void	put_door(t_data *data, t_vec_int pos)
{
	int	i;
	int	j;

	i = 0;
	while (i < CUBE_SIZE)
	{
		j = 0;
		if (i < CUBE_SIZE / 2)
		{
			while (j < CUBE_SIZE)
			{
				my_pixel_put(&data->img, pos.x + i, pos.y + j, CYAN);
				j++;
			}
		}
		else
		{
			while (j < CUBE_SIZE)
			{
				my_pixel_put(&data->img, pos.x + i, pos.y + j, BLACK);
				j++;
			}
		}
		i++;
	}
}

void	draw_line(t_data *data, t_vec_int incr, t_vec_int start_draw)
{
	int			size;
	t_vec_int	map_pos;

	size = CUBE_SIZE;
	while (++incr.x < MINIMAP_SIZE)
	{
		map_pos = set_vec_int(map_pos, start_draw.x + incr.x, \
										start_draw.y + incr.y);
		if (map_pos.y < (int)floor(data->height / size) && \
			map_pos.x < (int)ft_strlen(data->map[map_pos.y]) && \
			data->map[map_pos.y][map_pos.x] == '1')
		{
			put_color(data, (t_vec_int){incr.x * size, incr.y * size}, \
										WHEAT, size);
		}
		else if (map_pos.y < (int)floor(data->height / size) && \
			map_pos.x < (int)ft_strlen(data->map[map_pos.y]) && \
			data->map[map_pos.y][map_pos.x] == 'D')
			put_door(data, (t_vec_int){incr.x * size, incr.y * size});
		else
		{
			put_color(data, (t_vec_int){incr.x * size, incr.y * size}, \
										BLACK, size);
		}
	}
}

void	render_minimap(t_data *data)
{
	t_vec_int	incr;
	t_vec_int	start_draw;
	t_vec_int	player_pos;

	incr.y = -1;
	init_minimap(data, &start_draw, &player_pos);
	while (++incr.y < MINIMAP_SIZE)
	{
		incr.x = -1;
		draw_line(data, incr, start_draw);
	}
	draw_player(data, RED, player_pos.x, player_pos.y);
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
	static int	index = 0;
	static int	count = 0;

	count++;
	fill_field_of_view(data);
	render_3d(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	if (data->p.key_weopan)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[index], \
												(W - 2400) / 2, (H - 1100) / 2);
		if (count % 2 == 0)
			index++;
		if (index == 42)
		{
			data->p.key_weopan = 0;
			index = 0;
		}
	}
	else
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[0], \
												(W - 2400) / 2, (H - 1100) / 2);
	clr_window(data);
	return (0);
}
