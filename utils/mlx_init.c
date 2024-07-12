/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:13:52 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/12 09:16:46 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	my_free(t_data *data)
{
	free(data->mlx);
	free(data);
	exit(1);
}

int get_height(char	**arr)
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

t_data	*start_init_mlx(char **arr)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->height = get_height(arr) * CUBE_SIZE;
	data->width = get_long_line(arr) * CUBE_SIZE;
	data->mlx = mlx_init();
	if (!data->mlx)
		(perror("mlx: "), free(data), exit(1));
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	if (!data->mlx_win)
		(perror("mlx: "), my_free(data));
	data->img.p_img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img.p_img)
	{
		(perror("mlx: "), mlx_destroy_window(data->mlx, data->mlx_win));
		my_free(data);
	}
	data->img.p_pixel = mlx_get_data_addr(data->img.p_img, \
						&data->img.bit_pixel, \
						&data->img.len, &data->img.endian);
	if (!data->img.p_pixel)
	{
		(perror("mlx "), mlx_destroy_image(data->mlx, data->img.p_img));
		mlx_destroy_window(data->mlx, data->mlx_win);
		my_free(data);
	}
	return (data);
}
