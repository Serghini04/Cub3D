/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:10:45 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/17 10:27:10 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	init_weapon(t_data *data)
{
	int	i;

	i = 0;
	int x, y;
	while (i < 36)
	{
		char *path = ft_strjoin("textures/test/t" , ft_strjoin(ft_itoa(i + 1), ".xpm"));
		data->weapon[i] = mlx_xpm_file_to_image(data->mlx, path, &x, &y);
		if (!data->weapon[i])
			exit(1);
		i++;
	}
}

void	init_game(t_data *data, char **arr)
{
	int	i;
	int	j;
	int len;

	i = 0;
	data->num_rays = W / WALL_STRIP_WIDTH;
	data->rays = malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data);
		exit(1);
	}
	data->map = arr;
	data->p.move_speed = 8;
	data->p.turn_dir = 0;
	data->p.up_down = 0;
	data->p.key_weopan = 0;
	data->p.left_right = 0;
	data->index_weapon = 0;
	// data->c = BLUE;
	data->c = TEAL;
	data->f = SILVER;
	init_weapon(data);
	init_textures(data);
	while (i < data->height / CUBE_SIZE)
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
				data->p.angle = M_PI_2;
				data->p.rotation_speed = 0.03;
				return ;
			}
			j++;
		}
		i++;
	}
}

void    draw_line(float x1, float y1, t_data *data)
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
        my_pixel_put(&data->img, x0, y0, CORN_SILK, data);
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

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	set_vec(t_vec *vec, float x, float y)
{
	vec->x = x;
	vec->y = y;
}

void	f()
{
	system("leaks Cub3D");
}

int main ()
{
	t_data	*data;
	// char	*arr[] = {
	// 	"1111111111111111111111111111111111",
	// 	"1000000000000000000000000000000001",
	// 	"1000000000000000000000000000000001",
	// 	"1000101010101010000000000000001001",
	// 	"100000N00000000000000000000000001",
	// 	"1000000000000000000000000000001001",
	// 	"1000000000000000000000000000001001",
	// 	"1000011000000000000000000000001001",
	// 	"1000100001111111111111111111111001",
	// 	"1000000001111000000000000000000001",
	// 	"1000000001111000000000000000000001",
	// 	"1000000000000000000000000000000001",
	// 	"1111111111111111111111111111111111",
	// 	NULL
	// };
	char	*arr[] = {
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
        "101000N00000000001100000000000000000000000000001",
        "101000000001000001100000000000000000000000000001",
        "1010000000100000011000000000000000000000000000011111111",
        "1010000000000000011P00000000000000000000000000000000001",
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
        "   1000111111111111111111111111",
        "   1000111111111111111111111111",
        "   1000111111111111111111111111",
        "   1000111111111111111111111111",
        "   1111111111111111111111111111",
		NULL
    };

	atexit(f);
	data = start_init_mlx(arr);
	init_game(data, arr);
	mlx_loop_hook(data->mlx, loopfunc, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, onpress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, onrelease, data);
	mlx_loop(data->mlx);
	return (0);
}
