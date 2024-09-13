/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/12 17:39:23 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	render_3d(t_data *data)
{
    int		color;
    t_vec	pos[3];
    float	dist_to_camera;
    float	wall_height;
    int		i;

    i = 0;
    fill_field_of_view(data);
    int index;
    while (i < data->num_rays)
    {
        int texture_width = data->tex[data->rays[i].dir].width;
        int texture_height = data->tex[data->rays[i].dir].height;

        dist_to_camera = (data->width / 2) / tan(FOV / 2);
        wall_height = (float)CUBE_SIZE * dist_to_camera / data->rays[i].distance;
        set_vec(&pos[0], W, H);
        set_vec(&pos[1], i, max(0, pos[0].y / 2 - wall_height / 2));
        pos[2].x = data->rays[i].is_ver ? fmod(data->rays[i].to_hit_wall.y, (float)CUBE_SIZE) / CUBE_SIZE * texture_width
        : fmod(data->rays[i].to_hit_wall.x, (float)CUBE_SIZE) / CUBE_SIZE * texture_width;
        index = -1;
        int y = 0;
        while (y++ < pos[1].y)
            my_pixel_put(&data->img, i, y, data->c);
        while (++index < wall_height && ++pos[1].y < pos[0].y)
        {
            pos[2].y = (pos[1].y - (pos[0].y / 2 - wall_height / 2))
                / wall_height * texture_height;
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

int  min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

t_vec_int   set_vec_int(t_vec_int data, int x, int y)
{
    data.x = x;
    data.y = y;
    return (data);
}

void	init_minimap(t_data *d, t_vec_int *start_draw, t_vec_int *player_pos)
{
	start_draw->x = max(0, floor(d->p.pos.x / CUBE_SIZE) - MINIMAP_SIZE / 2);
	start_draw->y = max(0, floor(d->p.pos.y / CUBE_SIZE) - MINIMAP_SIZE / 2);
	player_pos->x = ((int)(d->p.pos.x / CUBE_SIZE) - start_draw->x) * CUBE_SIZE;
	player_pos->y = ((int)(d->p.pos.y / CUBE_SIZE) - start_draw->y) * CUBE_SIZE;
}

void render_minimap(t_data *data)
{
    t_vec_int   incr;
    t_vec_int   start_draw;
    t_vec_int	map_pos;
	t_vec_int	player_pos;

	incr.y = 0;
	init_minimap(data, &start_draw, &player_pos);
	while (incr.y < MINIMAP_SIZE)
	{
	    incr.x = 0;
		while(incr.x < MINIMAP_SIZE)
		{
			map_pos = set_vec_int(map_pos, start_draw.x + incr.x, start_draw.y + incr.y);
			if (map_pos.y < (int)floor(data->height /CUBE_SIZE) &&
			    map_pos.x < (int)ft_strlen(data->map[map_pos.y]) &&
			    data->map[map_pos.y][map_pos.x] == '1')
			    put_color(data, incr.x * CUBE_SIZE, incr.y * CUBE_SIZE, WHEAT, CUBE_SIZE);
			else
			    put_color(data, incr.x * CUBE_SIZE, incr.y * CUBE_SIZE, BLACK, CUBE_SIZE);
			incr.x++;
		}
		incr.y++;
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
	render_3d(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	if (data->p.key_weopan)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[index], (W - 2400) / 2, (H - 1100) / 2);
        if (count % 2 == 0)
		    index++;
		if (index == 42)
		{
			data->p.key_weopan = 0;
			index = 0;
		}
	}
	else
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[0], (W - 2400) / 2, (H - 1100) / 2);
	clr_window(data);
	return (0);
}
