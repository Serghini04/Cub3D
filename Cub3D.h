/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:11:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/15 20:18:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef Cub3D_H
#define Cub3D_H
// backlist ## good movie.
// House of the Dragon
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include <math.h>
#include <stdbool.h>


// Size :
# define CUBE_SIZE 20
# define PLAYER_SIZE 5
# define FOV_ANGLE 60 * (M_PI / 180)
# define WALL_STRIP_WIDTH 10

// # define Key_ECH 53
// # define KEY_A 	0
// # define KEY_W	13
// # define KEY_D	2
// # define KEY_S	1

// # define KEY_LEFT 	123
// # define KEY_RIGHT	124

# define Key_ECH 65307
# define KEY_A 	97
# define KEY_W	119
# define KEY_D	100
# define KEY_S	115

# define KEY_LEFT 	65361
# define KEY_RIGHT	65363

// Colors:
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PURPLE 0x800080

// data structure :
enum e_direction
{
	East,
	West,
	North,
	South,
};

typedef struct s_player
{
	float	x;
	float	y;
	int		up_down;
	int		left_right;
	int		turn_direction;
	int		direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
}	t_player;

typedef struct s_img
{
	void	*p_img;		//mlx_new_image()
	char	*p_pixel;
	int		len;
	int		bit_pixel;
	int		endian;
}	t_img;

// Point 2D
typedef struct s_point
{
	float	x;
	float	y;
} t_point;

typedef struct s_data
{
	int			WIDTH;
	int			HEIGHT;
	char		**map;
	void		*mlx;		// mlx_init();
	void		*mlx_win;	//mlx_new_window()
	t_img		img;		//mlx_new_image()
	t_player	p;			//data player
}	t_data;

// lib:
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
void	free_arr(char **res);

// utils:
int		loopfunc(t_data	*data);
int		onpress(int keycode, t_data *data);
int 	onrelease(int keycode, t_data *data);
bool	is_wall(float x, float y, t_data *data);
void    draw_line1(float x1, float y1, t_data *data);

// ray casting
t_point	ray_casting(float ray_angle, t_data *data);

// main
int	draw_wall(t_data *data);
t_data	*start_init_mlx(char **arr);

#endif