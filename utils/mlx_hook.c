/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:25:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/16 15:43:57 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

// you need to free data textures.
int	onpress(int k, t_data *data)
{
	if (k == KEY_ECH)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data->rays);
		free(data);
		exit(1);
	}
	if (k == KEY_W)
		data->p.up_down = 1;
	if (k == KEY_S)
		data->p.up_down = -1;
	if (k == KEY_LEFT)
		data->p.turn_dir = -1;
	if (k == KEY_RIGHT)
		data->p.turn_dir = 1;
	if (k == KEY_D)
		data->p.left_right = 1;
	if (k == KEY_A)
		data->p.left_right = -1;
	return (0);
}

int	onrelease(int k, t_data *data)
{
	if (k == KEY_W)
		data->p.up_down = 0;
	if (k == KEY_S)
		data->p.up_down = 0;
	if (k == KEY_LEFT)
		data->p.turn_dir = 0;
	if (k == KEY_RIGHT)
		data->p.turn_dir = 0;
	if (k == KEY_D)
		data->p.left_right = 0;
	if (k == KEY_A)
		data->p.left_right = 0;
	return (0);
}

bool	is_wall(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

    new_x = x / CUBE_SIZE;
    new_y = y / CUBE_SIZE;
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1')
		return (true);
	return (false);
}

bool	is_wall2(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

    new_x = x / CUBE_SIZE;
    new_y = y / CUBE_SIZE;
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1' || data->map[(int)floor(data->p.pos.y/CUBE_SIZE)][(int)floor(new_x)] == '1' || data->map[(int)floor(new_y)][(int)floor(data->p.pos.x/CUBE_SIZE)] == '1')
		return (true);
	return (false);
}

bool	is_wall1(float x, float y, t_data *data)
{
	int new_x = x / CUBE_SIZE;
	int new_y = y / CUBE_SIZE;
	int new_xx = (x + PLAYER_SIZE) / CUBE_SIZE;
	int new_yy = (y + PLAYER_SIZE) / CUBE_SIZE;
	if (new_x < 0 || new_x >= data->width || new_y < 0 || new_y >= data->height
		|| new_xx < 0 || new_xx >= data->width || new_yy < 0 || new_yy >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x) || (int)ft_strlen(data->map[(int)floor(new_yy)]) < (int)floor(new_xx))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1'
		|| data->map[(int)floor(new_yy)][(int)floor(new_xx)] == '1')
		return (true);
	return (false);
}

int	loopfunc(t_data	*data)
{
	float	x;
	float	y;
	float	move_step;

	move_step = data->p.up_down * data->p.move_speed;
	data->p.angle += data->p.turn_dir * data->p.rotation_speed;
	x = data->p.pos.x + cos(data->p.angle) * move_step;
	y = data->p.pos.y + sin(data->p.angle) * move_step;
	x += cos(data->p.angle + M_PI_2) * data->p.left_right \
									* (data->p.move_speed - 1);
	y += sin(data->p.angle + M_PI_2) * data->p.left_right \
									* (data->p.move_speed - 1);
	if (!is_wall2(x, y, data))
	{
		data->p.pos.x = x;
		data->p.pos.y = y;
	}
	start_rendering(data);
	return (0);
}
