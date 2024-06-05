/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:11:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/05 20:20:10 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef Cub3D_H
#define Cub3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>


// Size :
# define CUBE_SIZE 64
# define PLAYER_SIZE 5

# define KEY_A 	0
# define KEY_W	13
# define KEY_D	2
# define KEY_S	1

# define KEY_LEFT 	123
# define KEY_RIGHT	124

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

typedef struct s_keyboard
{
	bool	E;
	bool	W;
	bool	N;
	bool	S;
	bool	L;
	bool	R;
	int		key;
}	t_keyboard;

typedef struct s_img
{
	void	*p_img;		//mlx_new_image()
	char	*p_pixel;
	int		len;
	int		bit_pixel;
	int		endian;
}	t_img;

typedef struct s_data
{
	int			WIDTH;
	int			HEIGHT;
	char		**map;
	void		*mlx;		// mlx_init();
	void		*mlx_win;	//mlx_new_window()
	t_img		img;		//mlx_new_image()
	t_keyboard	keyboard;	// keyborad status keys
	t_player	p;			//data player
}	t_data;

// lib:
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
void	free_arr(char **res);

// utils:
int		onpress(int keycode, t_data *data);
int 	onrelease(int keycode, t_data *data);
int		loopfunc(t_data	*data);

int	draw_wall(t_data *data);
t_data	*start_init_mlx(char **arr);

#endif