/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:19 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/14 16:15:36 by rpandipe         ###   ########.fr       */
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

# define WIN_WIDTH			1024
# define WIN_HEIGHT			512
# define MINIMAP_WIDTH		512
# define MINIMAP_HEIGHT		512
# define CUB_WIDTH			512
# define CUB_HEIGHT			512
# define PIXELS_PER_CELL	32 // minimap size (x,y) / number of cells in my map : 512/16
# define CELLS_PER_PIXEL	0.03125 // number of cells in my map / minimap size (x,y) : 512/16
# define SIZE_PIXEL_PLAYER	9
# define MOVE_SPEED			5
# define ROTATION_SPEED		0.1
# define PI					3.1415926535
# define LINE_LENGTH		25
# define DR					0.0174533
# define TILE_SIZE			64
# define NUM_RAYS			64
# define M_SENSITIVITY		10
# define CROSSHAIR_LEN		10
# define CROSSHAIR_COLOR	0xFFFFFF

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef struct s_lst
{
	struct s_lst	*next;
	char			*line;
}	t_lst;

typedef struct s_ray
{
	float	x;
	float	y;
	float	angle;
}	t_ray;

typedef struct s_player
{
	int		is_found;
	float	x;
	float	y;
	int		mouse_x;
	int		mouse_y;
	float	angle;
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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

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

typedef struct s_texture
{
	t_text		north;
	t_text		south;
	t_text		east;
	t_text		west;	
}	t_texture;

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
}	t_data;

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */

void	check_arg(int argc, char **argv);
void    ft_error(const char *str);
/* ************************************************************************** */
void	err_parsing(char **line, int fd, t_data *data, t_lst **map_lst);
/* ************************************************************************** */
void	free_get_next_line(int fd, char **line);
void	free_env(t_data *data);
void	free_map(t_data *data);
void	free_lst(t_lst **map_lst);
void	free_cub3d(t_data *data);
/* ************************************************************************** */
void    parsing_file(char *filename, t_data *data);
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
void	init_data(t_data *data);
/* ************************************************************************** */
int		key_event(int keycode, void *param);
int		mouse_event(int x, int y, void *param);
int		close_event(void *param);
/* ************************************************************************** */
void	draw_pixel(t_img *img, int x, int y, int color);
int		convert_color(int r, int g, int b);
void	draw_crosshair(t_data *data);
/* ************************************************************************** */
void	draw_minimap(t_data *data);
void	draw_grid(t_data *data);
int		find_cell_color(int x, int y, t_data *data);
/* ************************************************************************** */
void	draw_player(t_data *data);
void	cast_rays(t_data *data);
/* ************************************************************************** */
void	move_player(int keycode, t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
/* ************************************************************************** */
void	redraw_minimap(t_data *data);
void	rotate_player(int keycode, t_data *data);
/* ************************************************************************** */
void	draw_line(t_data *data, int x_final, int y_final, int color);
void	draw_gradual(t_data *data, int dx, int dy, int color);
void	draw_steep(t_data *data, int dx, int dy, int color);
void	draw_ceiling(t_data *data);
void	draw_floor(t_data *data);
void	draw_cub(t_data *data, float dist, int r, float ray_angle, int color);

#endif