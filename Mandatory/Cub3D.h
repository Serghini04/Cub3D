/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:11:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/09/18 12:14:28 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>

// Size :
# define W 1776
# define H 1032
# define CUBE_SIZE 32
# define PLAYER_SIZE 5
# define BUFFER_SIZE 10
# define FOV 1.04
# define WALL_STRIP_WIDTH 1
# define SIZE_MINI_MAP 0.2

# define KEY_ECH 53
# define KEY_A 	0
# define KEY_W	13
# define KEY_D	2
# define KEY_S	1
# define KEY_Q	12
# define KEY_M	46

# define KEY_LEFT 	123
# define KEY_RIGHT	124

// linux :
// # define Key_ECH 65307
// # define KEY_A 	97
// # define KEY_W	119
// # define KEY_D	100
// # define KEY_S	115

// # define KEY_LEFT 	65361
// # define KEY_RIGHT	65363

// Colors:
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define CORN_SILK 0xFFF8DC
# define RED 0xFF0000
# define ORANGE 0xFFA500
# define LIME 0x00FF00
# define BLUE 0x87CEEB
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define SILVER 0xC0C0C0
# define GRAY 0x808080
# define MAROON 0x800000
# define OLIVE 0x808000
# define GREEN 0x008000
# define PURPLE 0x800080
# define TEAL 0x008080
# define NAVY 0x000080
# define WHEAT 0xF5DEB3

// data structure :
enum e_direction
{
	North,
	West,
	East,
	South,
};
// Point 2D
typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_player
{
	int		up_down;
	int		left_right;
	int		turn_dir;
	int		key_weopan;
	float	angle;
	float	move_speed;
	float	rotation_speed;
	t_vec	pos;
}	t_player;

typedef struct s_img
{
	void	*p_img;		//mlx_new_image()
	char	*p_pixel;
	int		len;
	int		bit_pixel;
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	angle;
	bool	is_up;
	bool	is_ver;
	bool	is_down;
	bool	is_left;
	bool	is_right;
	int		dir;
	float	distance;
	t_vec	to_hit_wall;
}	t_ray;

typedef struct s_textures
{
	char	*path;
	int		*add;
	int		width;
	int		height;
}	t_textures;

typedef struct s_data
{
	int				width;
	int				height;
	void			*weapon[37];
	int				index_weapon;
	unsigned int	f;
	unsigned int	c;
	int				num_rays;
	t_ray			*rays;
	char			**map;
	void			*mlx;		// mlx_init();
	void			*mlx_win;	//mlx_new_window()
	t_img			img;		//mlx_new_image()
	t_player		p;			//data player
	t_textures		*tex;
}	t_data;

typedef struct s_vec_int
{
	int	x;
	int	y;
}	t_vec_int;

typedef struct s_map
{
	unsigned int	floor;
	unsigned int	ceil;
	int				pos_x;
	int				pos_y;
	int				h;
	int				w;
	char			angle_view;
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	char			**tab_map;
	int				len;
}	t_map;

// lib:
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
char	*ft_strdup(char *s1);
void	free_arr(char **res);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
char	*stor_line(t_map *map, char *line);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// utils:
int		on_destroy(t_data *data);
float	max(float a, float b);
int		my_free(t_data *data);
int		loopfunc(t_data	*data);
void	init_textures(t_data *data);
int		onpress(int keycode, t_data *data);
int		onrelease(int keycode, t_data *data);
void	set_vec(t_vec *vec, float x, float y);
bool	is_wall(float x, float y, t_data *data);
int		get_color(t_data *data, int type, t_vec *pos);
void	my_pixel_put(t_img *img, int x, int y, int color);

// ray casting
float	check_angle(float angle);
void	fill_field_of_view(t_data *data);
t_ray	get_redirection_ray(float angle);
float	distance_two_points(t_vec a, t_vec b);
t_ray	ray_casting(float ray_angle, t_data *data);
t_vec	find_hor_intersection(t_ray	res, t_data *data);
t_vec	find_ver_intersection(t_ray res, t_data *data);

// main
void	start_init_mlx(t_data *data);
int		start_rendering(t_data *data);

// parce
void	run_error(t_map *map, char *line, int j);
void	runerror(t_map *map, char **arr, int i, int j);
void	seconde_part(t_map *map, int i, int j);
void	fill_data(t_map *map, t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char	*str_dup(char *s1);
char	*str_chr(char *s, int c);
char	*str_join(char *s1, char *s2);
char	*premier_ligne(char *ptr_of_bfr2);
char	*found_line(int fd, char **s_ptr);
void	*mem_cpy(void *dst, void *src, size_t n);
size_t	str_len(const char *s, char c);
int		ft_handel_input(t_map *map, t_data *data, char **av);
int		is_avalidchar(char c);
void	free_myallocation(t_map *map, int index);
int		is_player(char c);
void	check_namefile(char *name_map);
int		check_beginning(char *line);
void	check_colloers(char *line, t_map *map, int ret, int index_line);
void	ft_check_line(char *line, int index_line, t_map *map);
void	check_firstlastline(t_map *map, char **arr, int len);
void	check_linemap(t_map *map, char *line, int index_line, int *flag);
int		ft_allocmap(t_map *map, char **av);
int		check_input(char **av, t_map *map);
void	check_arrmap(t_map *map, int len);
void	check_spand0(char **arr, int *flag, int i, int j);
void	check_player(char **arr, int *flag, int i, int j);
void	check_devided(t_map *map, int len, int i, int j);
int		is_sp(char *line, int index);
char	*ft_storline(t_map *map, int i, int min_index);

#endif