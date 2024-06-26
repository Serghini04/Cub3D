#include "../Cub3D.h"

int	onpress(int k, t_data *data)
{
	if (k == Key_ECH)
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

bool	is_wall(float x, float y, t_data *data)
{
	int	new_x = x / CUBE_SIZE;
	int	new_y = y / CUBE_SIZE;
	// int new_xx = (x + PLAYER_SIZE) / CUBE_SIZE;
	// int new_yy = (y + PLAYER_SIZE) / CUBE_SIZE;
	if (x < 0 || x >= data->WIDTH || y < 0 || y >= data->HEIGHT
		/*|| new_xx < 0 || new_xx >= data->WIDTH || new_yy < 0 || new_yy >= data->HEIGHT*/)
		return (true);
	if (ft_strlen(data->map[(int)floor(new_y)]) < (int)floor(new_x) /*|| ft_strlen(data->map[(int)floor(new_yy)]) < (int)floor(new_xx)*/)
		return (true);
	// printf("(%d,%d)=>(%d,%d)\n", (int)floor(new_y), (int)floor(new_x), data->HEIGHT, data->WIDTH);
	if (data->map[(int)floor(new_y)][(int)floor(new_x)] == '1'
		/*|| data->map[(int)floor(new_yy)][(int)floor(new_xx)] == '1'*/)
		return (true);
	return (false);
}

int	loopfunc(t_data	*data)
{
	float	x;
	float	y;
	float	move_step = data->p.up_down * data->p.move_speed;

	data->p.rotation_angle += data->p.turn_direction * data->p.rotation_speed;
	x = data->p.pos.x + cos(data->p.rotation_angle) * move_step;
	y = data->p.pos.y + sin(data->p.rotation_angle) * move_step;
	x += cos(data->p.rotation_angle + M_PI_2) * data->p.left_right * (data->p.move_speed - 1);
	y += sin(data->p.rotation_angle + M_PI_2) * data->p.left_right * (data->p.move_speed - 1);
	if (!is_wall(x, y , data))
	{
		data->p.pos.x = x;
		data->p.pos.y = y;
	}
	draw_wall(data);
	return (0);
}
