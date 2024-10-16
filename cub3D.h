/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:19 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/18 15:24:55 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

# define PI					3.1415926535
# define WIN_WIDTH			1024
# define WIN_HEIGHT			512
# define MINIMAP_WIDTH		512
# define MINIMAP_HEIGHT		512
# define CUB_WIDTH			512
# define CUB_HEIGHT			512
# define PIXELS_PER_CELL	32 // minimap size (x,y) / number of cells in my map : 512/16
# define CELLS_PER_PIXEL	0.03125 // number of cells in my map / minimap size (x,y) : 16/512
# define SIZE_PIXEL_PLAYER	9
# define MOVE_SPEED			4
# define ROTATION_SPEED		2
# define LINE_LENGTH		25
# define FOV				60
# define DR					0.0174533
# define TILE_SIZE			64
# define NUM_RAYS			64
# define M_SENSITIVITY		10
# define CROSSHAIR_LEN		10
# define CROSSHAIR_COLOR	0xFFFFFF

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef enum e_type
{
	VERTICAL,
	HORIZONTAL,
}	t_type;

typedef struct s_lst
{
	struct s_lst	*next;
	char			*line;
}	t_lst;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_sprite
{
	float	x;
	float	y;
	int		visible;
	float	distance;
	t_img	img;
}	t_sprite;

typedef struct s_player
{
	int			is_found;
	float		x;
	float		y;
	int			mouse_x;
	int			mouse_y;
	float		angle;
	t_sprite	sprite;
}	t_player;

typedef struct s_color
{
	int	is_set;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_env
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_color		floor;
	t_color		ceiling;
	char		**map;
}	t_env;

typedef struct s_text
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_text;

typedef struct s_ray
{
	float	x;
	float	y;
	float	angle;
	float	dist;
	float	xo;
	float	yo;
	int		dof;
	t_text	text;
	t_type	type;
}	t_ray;

typedef struct s_texture
{
	t_text		north;
	t_text		south;
	t_text		east;
	t_text		west;	
}	t_texture;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		minimap;
	t_img		cub;
	t_texture	texture;
	t_env		env;
	t_player	player;
	int			map_width;
	int			map_height;
	t_keys		key;
	double		last_frame_time;
}	t_data;

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */

void	check_arg(int argc, char **argv);
void    ft_error(const char *str);
double	get_time(void);
double	update_time(t_data *data);
void	init_data(t_data *data);
/* ************************************************************************** */
void	err_parsing(char **line, int fd, t_data *data, t_lst **map_lst);
/* ************************************************************************** */
void	free_get_next_line(int fd, char **line);
void	free_env(t_data *data);
void	free_map(t_data *data);
void	free_lst(t_lst **map_lst);
void	free_cub3d(t_data *data);
/* ************************************************************************** */
void	parsing_file(char *filename, t_data *data);
void	parse_texture_color(char **line, int fd, t_data *data);
void	parse_map(char **line, int fd, t_lst **map_lst, t_data *data);
/* ************************************************************************** */
int		check_elem(char *line, t_env *env);
int		check_texture(char *line, t_env *env);
int		get_texture(char *line, char **path);
int		check_color(char *line, t_env *env);
int		get_color(char *line, t_color *elem);
/* ************************************************************************** */
int		check_map(t_lst **ptr, int *width, int *height, t_data *data);
int		check_player_and_width(char *line, int *width, t_player *player, \
int curr_height);
int		create_map(t_lst **map_lst, t_data *data);
int		map_closed(char **map, int width, int height);
/* ************************************************************************** */
int		add_node(char *line, t_lst **map_lst);
int		get_map_lst(char **line, int fd, t_lst **map_lst);
/* ************************************************************************** */
void	check_fd(int *fd, char *filename);
int		extract_one_color(int *i, char *line, int *color_elem);
int		go_next_color(int *i, char **line);
int		empty_line(char *line);
int		valid_line(char *line);
/* ************************************************************************** */
int		key_pressed(int keycode, void *param);
int		key_released(int keycode, void *param);
int		mouse_event(int x, int y, void *param);
int		player_event(t_data *data);
int		close_event(void *param);
/* ************************************************************************** */
void	draw_pixel(t_img *img, int x, int y, int color);
int		convert_color(int r, int g, int b);
void	draw_crosshair(t_data *data);
void	redraw_minimap(t_data *data);
/* ************************************************************************** */
void	draw_minimap(t_data *data);
void	draw_grid(t_data *data);
int		find_cell_color(int x, int y, t_data *data);
/* ************************************************************************** */
void	draw_player(t_data *data);

/* ************************************************************************** */
void	move_player(t_data *data, double delta_time);
void	compute_directional_movement(t_data *data, double *move_x, double *move_y, double move_speed);
int		can_move_to(double move_x, double move_y, t_data *data);
/* ************************************************************************** */
void	draw_line(t_data *data, int x_final, int y_final, int color);
void	draw_gradual(t_data *data, int dx, int dy, int color);
void	draw_steep(t_data *data, int dx, int dy, int color);
void	draw_ceiling(t_data *data);
void	draw_floor(t_data *data);
void	draw_cub(t_data *data, t_ray ray, int r);
int 	get_texture_color(t_text *texture, int x, int y);

void	draw_cub_scene(t_data *data);
void	process_and_draw_wall_slice(t_data *data, t_ray ray_v, t_ray ray_h, int r);
void	init_ray_data(t_data *data, t_ray *ray, int reinit, t_type type);
void	init_horizontal_ray(t_data *data, t_ray *ray, int px, int py);
void	init_vertical_ray(t_data *data, t_ray *ray, int px, int py);
void	determine_hit_ray(t_data *data, t_ray *ray);
void	calculate_distance(t_data *data, t_ray *ray);
void	normalize_angle(t_ray *ray);

#endif