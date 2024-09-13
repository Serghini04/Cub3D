/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:25:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/13 11:21:34 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

bool	is_valid_pos(int x, int y, t_data *data)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (false);
	if ((int)ft_strlen(data->map[y]) < x)
		return (false);
	return (true);
}

void open_door(t_data *data)
{
    int x, y;

    x = (int)floor(data->p.pos.x / CUBE_SIZE);
    y = (int)floor(data->p.pos.y / CUBE_SIZE);

    t_ray res = get_redirection_ray(data->p.angle);
    if (res.is_down && is_valid_pos(x, y + 1, data) && data->map[y + 1][x] == 'D')
		data->map[y + 1][x] = 'd';
	else if (res.is_up && is_valid_pos(x, y - 1, data) && data->map[y - 1][x] == 'D')
		data->map[y - 1][x] = 'd';
	else if (res.is_left && is_valid_pos(x + 1, y, data) && data->map[y][x + 1] == 'D')
		data->map[y][x + 1] = 'd';
	else if (res.is_left && is_valid_pos(x - 1, y, data) && data->map[y][x - 1] == 'D')
		data->map[y][x - 1] = 'd';
}

void close_door(t_data *data)
{
    int x, y;

    x = (int)floor(data->p.pos.x / CUBE_SIZE);
    y = (int)floor(data->p.pos.y / CUBE_SIZE);

    t_ray res = get_redirection_ray(data->p.angle);
    if (res.is_down && is_valid_pos(x, y + 1, data) && data->map[y + 1][x] == 'd')
		data->map[y + 1][x] = 'D';
	else if (res.is_up && is_valid_pos(x, y - 1, data) && data->map[y - 1][x] == 'd')
		data->map[y - 1][x] = 'D';
	else if (res.is_left && is_valid_pos(x + 1, y, data) && data->map[y][x + 1] == 'd')
		data->map[y][x + 1] = 'D';
	else if (res.is_left && is_valid_pos(x - 1, y, data) && data->map[y][x - 1] == 'd')
		data->map[y][x - 1] = 'D';
}

int	onpress(int k, t_data *data)
{
	if (k == KEY_ECH)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data->rays);
		exit(1);
	}
	if (k == KEY_Q)
		data->p.key_weopan = 1;
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
	if (k == KEY_M)
		data->mouse_enable = (data->mouse_enable == 0) * 1;
	if (k == KEY_O)
		open_door(data);
	else if (k == KEY_C)
		close_door(data);
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

int	mouse(int x, int y, t_data *data)
{
	(void)y;
	if (!data->mouse_enable)
		return (0);
    if (x < W / 2)
        data->p.angle += -0.03;
    else if (x > W / 2)
        data->p.angle += 0.03;
	mlx_mouse_move(data->mlx_win, W / 2, H / 2);
    return (0);
}

bool	is_wall(float x, float y, t_data *data, t_ray *res)
{
	int	new_x;
	int	new_y;

	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->door && data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D')
	{
		res->dir = Door;
		return (true);
	}
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1')
		return (true);
	return (false);
}

bool	is_door(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (new_x < 0 || new_x >= data->width || new_y < 0 || new_y >= data->height)
		return (false);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (false);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D')
		return (true);
	return (false);
}

bool	is_wall2(float x, float y, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = x / CUBE_SIZE;
	new_y = y / CUBE_SIZE;
	if (new_x < 0 || new_x >= data->width || new_y < 0 || new_y >= data->height)
		return (true);
	if ((int)ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x))
		return (true);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1' || \
	data->map[(int)floor(data->p.pos.y / CUBE_SIZE)][(int)floor(new_x)] == '1' \
	|| data->map[(int)floor(new_y)][(int)floor(data->p.pos.x / \
	CUBE_SIZE)] == '1')
		return (true);
	if (data->door && (data->map[(int)floor(new_y)][(int)floor(new_x)] == 'D' || \
	data->map[(int)floor(data->p.pos.y / CUBE_SIZE)][(int)floor(new_x)] == 'D' \
	|| data->map[(int)floor(new_y)][(int)floor(data->p.pos.x / \
	CUBE_SIZE)] == 'D'))
		return (true);
	return (false);
}

int	loopfunc(t_data	*data)
{
	float	x;
	float	y;
	float	move_step;

	if (data->mouse_enable)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
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
