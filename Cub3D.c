/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/15 00:02:08 by marvin           ###   ########.fr       */
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

	if (x < 0 || y < 0 || (x / CUBE_SIZE) > data->WIDTH || (y / CUBE_SIZE) > data->HEIGHT)
		return ;
	pos = (img->len * y) + (x * (img->bit_pixel / 8));
	*(int *)(img->p_pixel + pos) = color;
}

void	init_map(t_data *data, char **arr)
{
	int	i;
	int	j;
	int len;

	i = 0;
	data->map = arr;
	data->p.move_speed = 2.0;
	data->p.turn_direction = 0;
	data->p.up_down = 0;
	data->p.left_right = 0;
	while (i < data->HEIGHT)
	{
		j = 0;
		len = ft_strlen(arr[i]);
		while (j < len)
		{
			if (arr[i][j] == 'N')
			{
				data->p.x = (j * CUBE_SIZE);
				data->p.y = (i * CUBE_SIZE);
				data->p.x += (CUBE_SIZE / 2) - (PLAYER_SIZE / 2);
				data->p.y += (CUBE_SIZE / 2) - (PLAYER_SIZE / 2);
				data->p.direction = North;
				data->p.rotation_angle = M_PI_2;
				data->p.rotation_speed = (M_PI / 180);
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
	int	i;
	int	j;

	i = 0;

	while (i < pow)
	{
		j = 0;
		while (j < pow)
		{
			//  printf("x0 = %d   ------ y0 = %d\n", data->p.x, data->p.y);
			my_pixel_put(&data->img, data->p.x + i, data->p.y + j, color, data);
			j++;
		}
		i++;
	}
}

void    draw_line1(float x1, float y1, t_data *data)
{
	int x0 = data->p.x + (PLAYER_SIZE / 2);
	int y0 = data->p.y + (PLAYER_SIZE / 2);
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

void	draw_field_of_view(t_data *data)
{
	int		i;
	int		num_rays;
	float	ray_angle;
	t_point	hit_wall_hor;

	i = 0;
	num_rays = data->WIDTH / WALL_STRIP_WIDTH;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.rotation_angle - (FOV_ANGLE / 2);
	while (i < 1)
	{
		hit_wall_hor = ray_casting(ray_angle, data);
		// hit_wall_hor.x = data->p.x + (PLAYER_SIZE / 2) + cos(ray_angle) * 40;
		// hit_wall_hor.y = data->p.y + (PLAYER_SIZE / 2) + sin(ray_angle) * 40;
		draw_line1(hit_wall_hor.x, hit_wall_hor.y, data);
		ray_angle += FOV_ANGLE / num_rays;
		i++;
	}
}

int	draw_wall(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < data->HEIGHT)
	{
		j = 0;
		len = ft_strlen(data->map[i]);
		while (j < len)
		{
			if (data->map[i][j] == '1')
				put_color(data, j * CUBE_SIZE, i * CUBE_SIZE, WHITE, CUBE_SIZE);
			else
				put_color(data, j * CUBE_SIZE, i * CUBE_SIZE, BLACK, CUBE_SIZE);
			j += 1;
		}
		i += 1;
	}
	draw_player(data, RED, PLAYER_SIZE);
	t_point a;
	a.x = (data->p.x + (PLAYER_SIZE / 2)) + (cos(data->p.rotation_angle) * 50);
	a.y = (data->p.y + (PLAYER_SIZE / 2)) + (sin(data->p.rotation_angle) * 50);
	draw_line1(a.x, a.y, data);
	draw_field_of_view(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	return (0);
}

int main ()
{
	t_data	*data;
	char *arr[] = { "11111111111111111111",
					"10000000100000010001",
					"100N0000010000001001",
					"11111100000000000001",
					"10000000001111110001",
					"11100010000000100001",
					"10100001000000010001",
					"11111111111111111111", NULL};
	// char    *arr[] = {
    //     "           1111111111111111111111",
    //     "11100011111110000000000001",
    //     "   111100000111000000001111111111",
    //     " 1111000000000000000000001000000011",
    //     "111111111011000001110000011111111",
    //     "100000000011000001110111111111111",
    //     "1111111111110101111110010001",
    //     "      1111110111     1100011",
    //     "11111111111101011101010010001",
    //     "110000001101010111000000100011111111111111111111",
    //     "101000000000000001100000000000000000000000000001",
    //     "101000000000000001100000000000000000000000000001",
    //     "1010000000000000011000000000000000000000000000011111111",
    //     "1010000000N00000011P000000000000000000000000000000000001",
    //     "1010000000000000011000000000000000000000000000011111111",
    //     "101000000000000001100000000000000000000000000001",
    //     "110000001101010111000000100011111111111111111111",
    //     "101000000000000001100000000001",
    //     "10000000000000000000010010001",
    //     "110000011101111111110111100111",
    //     "10000000110101011100000010001",
    //     "100000000000000001100000000001",
    //     "10000000000000000000010010001",
    //     "110000011101111111110111100111",
    //     "11110001011        101101010111",
    //     "   1000111111111111111111111111",
    //     "   1000111111111111111111111111",
    //     "   1000111111111111111111111111",
    //     "   1000111111111111111111111111",
    //     "   1000111111111111111111111111",
    //     "   1111111111111111111111111111",
	// 	NULL
    // };

	data = start_init_mlx(arr);
	init_map(data, arr);
	mlx_loop_hook(data->mlx, loopfunc, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, onpress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, onrelease, data);
	mlx_loop(data->mlx);
	return (0);
}