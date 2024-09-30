/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:19 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/30 12:33:12 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/keysym.h>

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef struct s_lst
{
	struct s_lst	*next;
	char			*line;
}	t_lst;


typedef struct s_player
{
	int		is_found;
	float	x;
	float	y;
	float	speed;
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

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		minimap;
	t_img		cub;
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

#endif