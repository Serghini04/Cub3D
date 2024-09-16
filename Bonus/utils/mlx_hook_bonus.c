/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:25:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/16 17:35:35 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	open_door(t_data *data)
{
	int		x;
	int		y;
	t_ray	res;

	x = (int)floor(data->p.pos.x / CUBE_SIZE);
	y = (int)floor(data->p.pos.y / CUBE_SIZE);
	res = get_redirection_ray(data->p.angle);
	if (res.is_down && is_valid_pos(x, y + 1, data, 'D'))
		data->map[y + 1][x] = 'd';
	else if (res.is_up && is_valid_pos(x, y - 1, data, 'D'))
		data->map[y - 1][x] = 'd';
	else if (res.is_right && is_valid_pos(x + 1, y, data, 'D'))
		data->map[y][x + 1] = 'd';
	else if (res.is_left && is_valid_pos(x - 1, y, data, 'D'))
		data->map[y][x - 1] = 'd';
}

void	close_door(t_data *data)
{
	int		x;
	int		y;
	t_ray	res;

	x = (int)floor(data->p.pos.x / CUBE_SIZE);
	y = (int)floor(data->p.pos.y / CUBE_SIZE);
	res = get_redirection_ray(data->p.angle);
	if (res.is_down && is_valid_pos(x, y + 1, data, 'd'))
		data->map[y + 1][x] = 'D';
	else if (res.is_up && is_valid_pos(x, y - 1, data, 'd'))
		data->map[y - 1][x] = 'D';
	else if (res.is_right && is_valid_pos(x + 1, y, data, 'd'))
		data->map[y][x + 1] = 'D';
	else if (res.is_left && is_valid_pos(x - 1, y, data, 'd'))
		data->map[y][x - 1] = 'D';
}

int	onpress(int k, t_data *data)
{
	if (k == KEY_ECH)
		my_free(data);
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
	if (k == KEY_C)
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
