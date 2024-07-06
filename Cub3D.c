/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/06 16:52:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

// char *arr[] = { "11111111111111111111",
// 				"10000000100000010001",
// 				"10000000100000010001",
// 				"11111100000000000001",
// 				"10000000001111110001",
// 				"10000001000000010001",
// 				"10000001000000010001",
// 				"11111111111111111111", NULL};

void	my_pixel_put(t_img *img, int x, int y, int color, t_data *data)
{
	int	pos;

	if (x < 0 || y < 0 || x >= data->WIDTH || y >= data->HEIGHT)
		return ;
	pos = (img->len * y) + (x * (img->bit_pixel / 8));
	*(int *)(img->p_pixel + pos) = color;
}

void	init_map(t_data *data, char **arr)
{
	int	i;
	int	j;
	int len;
	int	num_rays;

	i = 0;
	data->num_rays = data->WIDTH / WALL_STRIP_WIDTH;
	data->rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data);
		exit(1);
	}
	data->map = arr;
	data->p.move_speed = 0.6;
	data->p.turn_direction = 0;
	data->p.up_down = 0;
	data->p.left_right = 0;
	init_textures(data);
	while (i < data->HEIGHT / CUBE_SIZE)
	{
		j = 0;
		len = ft_strlen(arr[i]);
		while (j < len)
		{
			if (arr[i][j] == 'N')
			{
				data->p.pos.x = (j * CUBE_SIZE);
				data->p.pos.y = (i * CUBE_SIZE);
				data->p.pos.x += (CUBE_SIZE / 2);
				data->p.pos.y += (CUBE_SIZE / 2);
				data->p.direction = North;
				data->p.rotation_angle = M_PI_2;
				data->p.rotation_speed = 0.8 * (M_PI / 180);
				return ;
			}
			j++;
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
			//  printf("x0 = %d   ------ y0 = %d\n", data->p.pos.x, data->p.pos.y);
			my_pixel_put(&data->img, p.x + i, p.y + j, color, data);
			j++;
		}
		i++;
	}
}

void    draw_line1(float x1, float y1, t_data *data)
{
	int x0 = data->p.pos.x + (PLAYER_SIZE / 2);
	int y0 = data->p.pos.y + (PLAYER_SIZE / 2);
	x0 *= SIZE_MINI_MAP;
	y0 *= SIZE_MINI_MAP;
    int dx = fabs(round(x1) - x0);
    int dy = fabs(round(y1) - y0);
    int sx = x0 < round(x1) ? 1 : -1;
    int sy = y0 < round(y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
        my_pixel_put(&data->img, x0, y0, RED, data);
        if (x0 == round(x1) && y0 == round(y1))
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	fill_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.rotation_angle - (FOV_ANGLE / 2);
	while (i < data->num_rays)
	{
		data->rays[i] = ray_casting(ray_angle, data);
		// hit_wall_hor.x = data->p.pos.x + (PLAYER_SIZE / 2) + cos(ray_angle) * 40;
		// hit_wall_hor.y = data->p.pos.y + (PLAYER_SIZE / 2) + sin(ray_angle) * 40;
		// draw_line1(data->rays[i].to_hit_wall.x * SIZE_MINI_MAP, data->rays[i].to_hit_wall.y * SIZE_MINI_MAP, data);
		ray_angle += FOV_ANGLE / data->num_rays;
		i++;
	}
}

void	draw_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.rotation_angle - (FOV_ANGLE / 2);
	while (i < data->num_rays)
	{
		draw_line1(data->rays[i].to_hit_wall.x * SIZE_MINI_MAP, data->rays[i].to_hit_wall.y * SIZE_MINI_MAP, data);
		ray_angle += FOV_ANGLE / data->num_rays;
		i++;
	}
}


void	clr_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->HEIGHT)
	{
		j = 0;
		while (j < data->WIDTH)
		{
			my_pixel_put(&data->img, j, i, BLACK, data);
			j++;
		}
		i++;
	}
}

void draw_rect(t_data *data, int x_start, int y_start, int width, int height) {
    int x_end = x_start + width;
    int y_end = y_start + height;

    for (int x = x_start; x < x_end; x++) {
        for (int y = y_start; y < y_end; y++) {
            my_pixel_put(&data->img, x, y, 0xFF2555, data); // Change 0xFFFFFF to the color you want
        }
    }
}
	// float	distance_Projection;
	// float	wall_strip_Height;
	// float	y;
	// float	top_wall;
	// float	bottom_wall;
		// distance_Projection = (data->WIDTH / 2) / tan(FOV_ANGLE / 2);
		// wall_strip_Height = (CUBE_SIZE / (data->rays[i].distance * cos(data->rays[i].angle - data->p.rotation_angle))) * distance_Projection;

		// // find top & bottom6
		// top_wall = (data->HEIGHT / 2) - (wall_strip_Height / 2);
		// top_wall = top_wall < 0 ? 0 : top_wall;
		// bottom_wall = (data->HEIGHT / 2) + (wall_strip_Height / 2);
		// bottom_wall = bottom_wall > data->HEIGHT ? data->HEIGHT : bottom_wall;
		// y = top_wall;

float	radconvert(float degree)
{
	float	rad;

	rad = degree * M_PI / 180;
	return (rad);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

int get_color(t_data *data, int type, t_vec *pos)
{

	int of = ((int)data->tex[type].WIDTH *
						(int)pos->y + (int)pos->x);
	if ((int)pos->x >= 0 && (int)pos->x < data->tex[type].WIDTH &&
			(int)pos->y >= 0 && (int)pos->y < data->tex[type].HEIGHT)
	{
		return (*(data->tex[type].add + of));
	}
	return (0x0);
}

void	set_pos(t_vec *pos, float x, float y)
{
	pos->x = x;
	pos->y = y;
}

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
	while (i < data->WIDTH)
	{
		int		color;
		t_vec	pos[3];
		float	dist_to_camera;
		float	wall_height;

		dist_to_camera = (data->WIDTH / 2) / tan(FOV_ANGLE / 2);
		wall_height = a * dist_to_camera / data->rays[i].distance;
		set_pos(&pos[0], data->WIDTH, data->HEIGHT);
		set_pos(&pos[1], i,
			max(0, pos[0].y / 2 - wall_height / 2));
		pos[2].x = data->rays[i].is_ver ?
		(int)fmod(data->rays[i].to_hit_wall.y, a) / a
		* 64:
		(int)fmod(data->rays[i].to_hit_wall.x, a) / a
		* 64;
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

int	draw_wall(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	render_3d(data);
	// WALL MINI MAP.
	while (i * CUBE_SIZE < data->HEIGHT)
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
	// t_vec a;
	// a.x = (data->p.pos.x + (PLAYER_SIZE / 2)) + (cos(data->p.rotation_angle) * 50);
	// a.y = (data->p.pos.y + (PLAYER_SIZE / 2)) + (sin(data->p.rotation_angle) * 50);
	// a.x *= SIZE_MINI_MAP;
	// a.y *= SIZE_MINI_MAP;
	// draw_line1(a.x, a.y, data);
	draw_field_of_view(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	clr_window(data);
	return (0);
}

int main ()
{
	t_data	*data;
// 	char *arr[] = {
//     "11111111111111111111",
//     "10000000000000000001",
//     "10000000000000000001",
//     "10001010101010101001",
//     "100000N000000000001",
//     "10000000000000001001",
//     "10000000000000001001",
//     "10000110000000001001",
//     "10001000011111111001",
//     "10000000011110000001",
//     "10000000011110000001",
//     "10000000000000000001",
//     "11111111111111111111",
// 	NULL
// };
	char    *arr[] = {
        "           1111111111111111111111",
        "11100011111110000000000001",
        "   111100000111000000001111111111",
        " 1111000000000000000000001000000011",
        "111111111011000001110000011111111",
        "100000000011000001110111111111111",
        "1111111111110101111110010001",
        "      1111110111     1100011",
        "11111111111101011101010010001",
        "110000001101010111000000100011111111111111111111",
        "101000000000000001100000000000000000000000000001",
        "101000000000000001100000000000000000000000000001",
        "1010000000000000011000000000000000000000000000011111111",
        "1010000000000000011P000000000000000000000000000000000001",
        "1010000000000000011000000000000000000000000000011111111",
        "101000000000000001100000000000000000000000000001",
        "110000001101010111000000100011111111111111111111",
        "101000000000000001100000000001",
        "10000000000000000000010010001",
        "110000011101111111110111100111",
        "10000000110101011100000010001",
        "100000000000000001100000000001",
        "10000000000000000000010010001",
        "110000011101111111110111100111",
        "11110001011        101101010111",
        "   1000111111111111111111111111",
        "   10N0111111111111111111111111",
        "   1000111111111111111111111111",
        "   1000111111111111111111111111",
        "   1000111111111111111111111111",
        "   1111111111111111111111111111",
		NULL
    };

	data = start_init_mlx(arr);
	init_map(data, arr);
	mlx_loop_hook(data->mlx, loopfunc, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, onpress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, onrelease, data);
	mlx_loop(data->mlx);
	return (0);
}