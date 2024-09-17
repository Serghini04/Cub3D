/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:13:52 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/17 14:05:38 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

int	get_height(char	**arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (0);
	while (arr[count])
		count++;
	return (count);
}

int	get_long_line(char **arr)
{
	int	long_line;
	int	len_line;
	int	i;

	i = 0;
	long_line = 0;
	while (arr[i])
	{
		len_line = ft_strlen(arr[i]);
		if (len_line > long_line)
			long_line = len_line;
		i++;
	}
	return (long_line);
}

void	start_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		(perror("mlx: "), free(data), exit(1));
	data->mlx_win = mlx_new_window(data->mlx, W, H, "Cub3D");
	if (!data->mlx_win)
		(perror("mlx: "), free(data), exit(1));
	data->img.p_img = mlx_new_image(data->mlx, W, H);
	if (!data->img.p_img)
		(perror("mlx: "), free(data), exit(1));
	data->img.p_pixel = mlx_get_data_addr(data->img.p_img, \
						&data->img.bit_pixel, \
						&data->img.len, &data->img.endian);
	if (!data->img.p_pixel)
		(perror("mlx: "), free(data), exit(1));
}

void	fill_data(t_map *map, t_data *data)
{
	data->map = map->tab_map;
	data->num_rays = W;
	data->tex = malloc(sizeof(t_textures) * 5);
	if (!data->tex)
		exit(1);
	data->tex[North].path = map->tex_no;
	data->tex[West].path = map->tex_we;
	data->tex[South].path = map->tex_so;
	data->tex[East].path = map->tex_ea;
	data->tex[Door].path = "textures/door.xpm";
	(1) && (data->c = map->ceil, data->f = map->floor);
	data->height = get_height(data->map) * CUBE_SIZE;
	data->width = get_long_line(data->map) * CUBE_SIZE;
	data->p.pos.x = map->pos_x * CUBE_SIZE;
	data->p.pos.y = map->pos_y * CUBE_SIZE;
	data->p.pos.x += (CUBE_SIZE / 2);
	data->p.pos.y += (CUBE_SIZE / 2);
	data->p.angle = 3 * M_PI / 2;
	data->p.rotation_speed = 0.03;
	data->p.move_speed = 8;
	data->p.turn_dir = 0;
	data->p.up_down = 0;
	data->p.key_weopan = 0;
	data->p.left_right = 0;
	data->mouse_enable = 1;
}
