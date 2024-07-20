/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/20 12:15:16 by meserghi         ###   ########.fr       */
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
			    put_color(data, x, y, WHEAT, size);
			else if (data->map[i][j] != ' ')
			    put_color(data, x, y, BLACK, size);
			j++;
		}
		i++;
	}
	draw_player(data, RED, 1);
	draw_field_of_view(data);
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
	int				i;
	static int	index = 0;
	static int	count = 0;

	count++;
	render_3d(data);
	rendering_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	if (count % 10 == 0)
	{
		if (!data->p.up_down)
			data->index_weapon = 0;
		else if (data->p.up_down && data->index_weapon == 0)
			data->index_weapon = 34;
		else if (data->p.up_down && data->index_weapon == 34)
			data->index_weapon = 35;
		else if (data->p.up_down && data->index_weapon == 35)
			data->index_weapon = 0;
	}
	i = data->index_weapon;
	if (data->p.key_weopan)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[index], (W - 1000) / 2, (H - 50) / 2);
		index++;
		if (index == 35)
		{
			data->p.key_weopan = 0;
			index = 0;
		}
	}
	else
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[i], (W - 1000) / 2, (H - 50) / 2);
	clr_window(data);
	return (0);
}
