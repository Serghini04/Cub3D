/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:27:01 by meserghi          #+#    #+#             */
/*   Updated: 2024/07/17 21:27:03 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

int	*copy_img(t_data *data, t_img res, int i, int bytes_per_pixel)
{
	int	x;
	int	y;
	int	*add;
	int	pixel_index;
	int	pixel_data;

	add = malloc(sizeof(int) * (data->tex[i].width * data->tex[i].height));
	if (!add)
		return (NULL);
	y = -1;
	while (++y < data->tex[i].height)
	{
		x = -1;
		while (++x < data->tex[i].width)
		{
			pixel_index = (y * data->tex[i].width + x) * bytes_per_pixel;
			pixel_data = *(int *)(res.p_pixel + pixel_index);
			add[y * data->tex[i].width + x] = pixel_data;
		}
	}
	return (add);
}

int	*convert_xpm_to_arr(t_data *data, char *path_img, int i)
{
	t_img	res;
	int		bytes_per_pixel;

	if (!path_img)
		return (NULL);
	res.p_img = mlx_xpm_file_to_image(data->mlx, path_img, \
							&data->tex[i].width, &data->tex[i].height);
	if (!res.p_img)
		exit (1);
	res.p_pixel = mlx_get_data_addr(res.p_img, &res.bit_pixel, \
												&res.len, &res.endian);
	if (!res.p_pixel)
		exit (1);
	bytes_per_pixel = res.bit_pixel / 8;
	return (copy_img(data, res, i, bytes_per_pixel));
}

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	data->path_imgs = malloc(sizeof(char *) * 5);
	if (!data->path_imgs)
		exit(1);
	data->path_imgs[South] = ft_strdup("textures/SO.xpm");
	data->path_imgs[East] = ft_strdup("textures/new.xpm");
	data->path_imgs[North] = ft_strdup("textures/new1.xpm");
	data->path_imgs[West] = ft_strdup("textures/wall.xpm");
	data->path_imgs[4] = NULL;
	data->tex = malloc(sizeof(t_textures) * 5);
	if (!data->tex)
		exit(1);
	while (i < 5)
	{
		data->tex[i].add = convert_xpm_to_arr(data, data->path_imgs[i], i);
		i++;
	}
}
