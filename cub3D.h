/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:19 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/16 16:42:46 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include "minilibx-linux/mlx.h"

# define WIN_WIDTH	1024
# define WIN_HEI	512
# define IMG_WIDTH	512
# define IMG_HEI	512

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef struct s_player
{
	int	flag;
	int	x;
	int	y;
}	t_player;

typedef struct s_lst
{
	struct s_lst	*next;
	struct s_lst	*prev;
	char			*line;
}	t_lst;

typedef struct s_color
{
	int	flag;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map_spec
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
	char	**map;
	int		start_x;
	int		start_y;
	int		width;
	int		height;
}	t_map_spec;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;


typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		minimap;
	t_img		cub;
	t_map_spec	*map_data;
}	t_data;

//scene

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */

void	check_arg(int argc, char **argv);
void	check_fd(int *fd, char *filename);
void	init_data(t_map_spec *map_data);
void	free_map_data(t_map_spec *data);
void	parse_info(char **line, int fd, t_map_spec *data);
int		check_info(char *line, t_map_spec *data);
int		check_texture(char *line, t_map_spec *data);
int		get_texture(char *line, char **path);
int		get_color(char *line, t_color *element);
int		extract_one_color(int *i, char *line, int *color_element);
int		go_next_color(int *i, char **line);
int		get_raw_map(char **line, int fd, t_lst **raw_map);
int		empty_line(char *line);
int		valid_line(char *line);
int		add_node(char *line, t_lst	**lst);
void	free_lst(t_lst *lst);
void	free_map(t_map_spec *data);
void	free_get_next_line(int fd, char **line);
void	parsing(char *filename, t_data *data);
void	parse_map(t_lst *raw_map, t_map_spec *data);
int		check_map(t_lst **ptr, int *width, int *height, t_map_spec *map_data);
int		check_player_and_width(char *line, int *width, t_player *player, \
int curr_height);
void	create_map(t_lst *raw_map, t_map_spec *data);
int		map_closed(char **map, int width, int height);
void	err_parsing(char **line, int fd, t_map_spec *data);
void	err_map(t_lst *raw_map, t_map_spec *data);
void	err_malloc(int fd);

void	cub_init(t_data *data);
int		convert_color(int r, int g, int b);

#endif