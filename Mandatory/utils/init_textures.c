/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:28:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/07 16:37:37 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
	//////////check this and free all allocation /////////
	if (!res.p_img)
	{
		printf("%s\n", path_img);
		printf("invalid PNGPATH !!\n");
		exit (1);
	}
	res.p_pixel = mlx_get_data_addr(res.p_img, &res.bit_pixel, \
												&res.len, &res.endian);
	if (!res.p_pixel)
		exit (1);
	bytes_per_pixel = res.bit_pixel / 8;
	return (copy_img(data, res, i, bytes_per_pixel));
}

// you need to free data textures./////
void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->tex[i].add = convert_xpm_to_arr(data, data->tex[i].path, i);
		i++;
	}
}
