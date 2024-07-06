#include "../Cub3D.h"

int *convert_xpm_to_arr(t_data *data, char *path_img, int i)
{
    int x, y;
    t_img res;
    int *add;

    if (!path_img)
        return (NULL);
    res.p_img = mlx_xpm_file_to_image(data->mlx, path_img, &data->tex[i].WIDTH, &data->tex[i].HEIGHT);
    if (!res.p_img)
        exit(1);
    res.p_pixel = mlx_get_data_addr(res.p_img, &res.bit_pixel, &res.len, &res.endian);
    if (!res.p_pixel)
        exit(1);
    add = (int *)malloc(sizeof(int) * (data->tex[i].WIDTH * data->tex[i].HEIGHT));
    if (!add)
        return (NULL);
    // Assuming 32 bits per pixel for simplicity
    int bytes_per_pixel = res.bit_pixel / 8;
    for (y = 0; y < data->tex[i].HEIGHT; y++)
    {
        for (x = 0; x < data->tex[i].WIDTH; x++)
        {
            int pixel_index = (y * data->tex[i].WIDTH + x) * bytes_per_pixel;
            // Assuming the pixel data is stored in ARGB format
            int pixel_data = *(int *)(res.p_pixel + pixel_index);
            add[y * data->tex[i].WIDTH + x] = pixel_data;
        }
    }
    return add;
}

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	data->path_imgs = malloc(sizeof(char *) * 5);
	if (!data->path_imgs)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		//you need to free data textures.
		free(data->rays);
		free(data);
		exit(1);
	}
	data->path_imgs[0] = NULL;
	data->path_imgs[1] = NULL;
	data->path_imgs[North] = ft_strdup("textures/n.xpm");
	data->path_imgs[3] = NULL;
	data->path_imgs[4] = NULL;
	data->tex = malloc(sizeof(t_textures) * 5);
	if (!data->tex)
	{
		mlx_destroy_image(data->mlx, data->img.p_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		// you need to free data textures.
		free(data->rays);
		free(data);
		exit(1);
	}
	while (i < 5)
	{
		data->tex[i].add = convert_xpm_to_arr(data, data->path_imgs[i], i);
		i++;
	}
}
