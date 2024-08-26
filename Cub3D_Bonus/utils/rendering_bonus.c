/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:42:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/08/21 17:01:29 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D_bonus.h"

void	render_3d(t_data *data)
{
    int		color;
    t_vec	pos[3];
    float	dist_to_camera;
    float	wall_height;
    int		i;

    i = 0;
    fill_field_of_view(data);
    int index;
    while (i < data->num_rays)
    {
        int texture_width = data->tex[data->rays[i].dir].width;
        int texture_height = data->tex[data->rays[i].dir].height;

        dist_to_camera = (data->width / 2) / tan(FOV / 2);
        wall_height = (float)CUBE_SIZE * dist_to_camera / data->rays[i].distance;
        set_vec(&pos[0], W, H);
        set_vec(&pos[1], i, max(0, pos[0].y / 2 - wall_height / 2));
        pos[2].x = data->rays[i].is_ver ? fmod(data->rays[i].to_hit_wall.y, (float)CUBE_SIZE) / CUBE_SIZE * texture_width
        : fmod(data->rays[i].to_hit_wall.x, (float)CUBE_SIZE) / CUBE_SIZE * texture_width;
        index = -1;
        int y = 0;
        while (y++ < pos[1].y)
            my_pixel_put(&data->img, i, y, data->c);
        while (++index < wall_height && ++pos[1].y < pos[0].y)
        {
            pos[2].y = (pos[1].y - (pos[0].y / 2 - wall_height / 2))
                / wall_height * texture_height;
            color = get_color(data, data->rays[i].dir, &pos[2]);
            if (color)
                my_pixel_put(&data->img, pos[1].x, pos[1].y, color);
        }
        while (pos[1].y++ < pos[0].y)
            my_pixel_put(&data->img, i, pos[1].y, data->f);
        i++;
    }
}

void	put_color(t_data *data, int x, int y, int color, int pow)
{
	int	i;
	int	j;

	i = 0;
	while (i < pow)
	{
		j = 0;
		while (j < pow)
		{
			my_pixel_put(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int color, int player_x, int player_y)
{
    int		i;
    int		j;
    t_vec	p;

    i = 0;

    p.x = player_x + (CUBE_SIZE / 2);
    p.y = player_y + (CUBE_SIZE / 2);
    while (i < PLAYER_SIZE)
    {
        j = 0;
        while (j < PLAYER_SIZE)
        {
            my_pixel_put(&data->img, p.x + i, p.y + j, color);
            j++;
        }
        i++;
    }
}

void	draw_field_of_view(t_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	// start first ray subtracting half of the FOV;
	ray_angle = data->p.angle - (FOV / 2);
	while (i < data->num_rays)
	{
		draw_line(data->rays[i].to_hit_wall.x * SIZE_MINI_MAP, data->rays[i].to_hit_wall.y * SIZE_MINI_MAP, data);
		ray_angle += FOV / data->num_rays;
		i++;
	}
}
// void	rendering_minimap(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;

// 	while (i * CUBE_SIZE < data->height)
// 	{
// 		j = 0;
//     	len = ft_strlen(data->map[i]);
// 		while (j < len)
// 		{
// 			int x = ceil((j * CUBE_SIZE) * SIZE_MINI_MAP);
// 			int y = ceil((i * CUBE_SIZE) * SIZE_MINI_MAP);
// 			int size = ceil(CUBE_SIZE * SIZE_MINI_MAP);
// 			if (data->map[i][j] == '1')
// 			    put_color(data, x, y, WHEAT, size);
// 			else if (data->map[i][j] != ' ')
// 			    put_color(data, x, y, BLACK, size);
// 			j++;
// 		}
// 		i++;
// 	}
// 	draw_player(data, RED, 1);
// 	draw_field_of_view(data);
// }


int  min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
#define MINIMAP_SIZE 7 // Fixed size of the minimap (7x7 tiles)

void render_minimap(t_data *data)
{
    int i, j;

    // Calculate the player's position in terms of map tiles
    int player_tile_x = data->p.pos.x / CUBE_SIZE;
    int player_tile_y = data->p.pos.y / CUBE_SIZE;

    // Determine the top-left corner of the minimap (centered on the player)
    int start_i = max(0, player_tile_y - MINIMAP_SIZE / 2);
    int start_j = max(0, player_tile_x - MINIMAP_SIZE / 2);

    // Loop through each tile in the minimap area
    for (i = 0; i < MINIMAP_SIZE; i++)
    {
        for (j = 0; j < MINIMAP_SIZE; j++)
        {
            // Determine the actual map coordinates of the current minimap tile
            int map_tile_x = start_j + j;
            int map_tile_y = start_i + i;

            // Calculate the screen coordinates of where to draw the tile on the minimap
            int screen_x = j * CUBE_SIZE;
            int screen_y = i * CUBE_SIZE;

            // Determine the color to draw: WHEAT for walls ('1'), BLACK for empty spaces
            if (map_tile_y < data->height &&
                map_tile_x < ft_strlen(data->map[map_tile_y]) &&
                data->map[map_tile_y][map_tile_x] == '1')
                put_color(data, screen_x, screen_y, WHEAT, CUBE_SIZE);
            else
                put_color(data, screen_x, screen_y, BLACK, CUBE_SIZE);
        }
    }

    // Calculate player's position on the minimap
    int minimap_player_x = (player_tile_x - start_j) * CUBE_SIZE;
    int minimap_player_y = (player_tile_y - start_i) * CUBE_SIZE;

    // Draw the player on the minimap
    draw_player(data, RED, minimap_player_x, minimap_player_y);
}



void	clr_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height / CUBE_SIZE)
	{
		j = 0;
		while (j < data->width / CUBE_SIZE)
		{
			my_pixel_put(&data->img, j, i, BLACK);
			j++;
		}
		i++;
	}
}

int	start_rendering(t_data *data)
{
	static int	index = 0;
	static int	count = 0;

	count++;
	render_3d(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.p_img, 0, 0);
	if (data->p.key_weopan)
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[index], (W - 2400) / 2, (H - 1100) / 2);
        if (count % 2 == 0)
		    index++;
		if (index == 42)
		{
			data->p.key_weopan = 0;
			index = 0;
		}
	}
	else
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[0], (W - 2400) / 2, (H - 1100) / 2);
        // if (i == 60)
        //     i = 43;
	clr_window(data);
	return (0);
}
