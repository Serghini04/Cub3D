/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:12:47 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/05 20:21:10 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	onpress(int k, t_data *data)
{
	data->keyboard.key = k;
	if (k == 53)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data);
		exit(0);
	}
	///     13 /\
	///	0<-    ||	->2
	///      1 \/
	/// <- 123 || 124 ->
	if (k == KEY_W)
		data->p.up_down = 1;
	if (k == KEY_S)
		data->p.up_down = -1;
	if (k == KEY_LEFT)
		data->p.turn_direction = -1;
	if (k == KEY_RIGHT)
		data->p.turn_direction = 1;
	if (k == KEY_D)
		data->p.left_right = 1;
	if (k == KEY_A)
		data->p.left_right = -1;
	return (0);
}

int onrelease(int k, t_data *data)
{
	if (k == KEY_W)
		data->p.up_down = 0;
	if (k == KEY_S)
		data->p.up_down = 0;
	if (k == KEY_LEFT)
		data->p.turn_direction = 0;
	if (k == KEY_RIGHT)
		data->p.turn_direction = 0;
	if (k == KEY_D)
		data->p.left_right = 0;
	if (k == KEY_A)
		data->p.left_right = 0;
	return (0);
}

int	loopfunc(t_data	*data)
{
	data->p.rotation_angle += data->p.turn_direction * data->p.rotation_speed;
	float	move_step = data->p.up_down * data->p.move_speed;
	data->p.x = data->p.x + cos(data->p.rotation_angle) * move_step;
	data->p.y = data->p.y + sin(data->p.rotation_angle) * move_step;
	data->p.x += cos(data->p.rotation_angle + M_PI_2) * data->p.left_right * (data->p.move_speed - 1);
	data->p.y += sin(data->p.rotation_angle + M_PI_2) * data->p.left_right * (data->p.move_speed - 1);
	draw_wall(data);
	return (0);
}
