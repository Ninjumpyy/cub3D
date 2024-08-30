/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:30:19 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/30 16:56:59 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
#include <fcntl.h>

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef	struct s_lst
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

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
	char	**map;		
}	t_data;

//scene

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */

void	check_arg(int argc, char **argv);
void	check_fd(int fd);
void	init_data(t_data *data);
void	free_data(t_data *data);
void	parse_info(char **line, int fd, t_data *data);
int		check_info(char *line, t_data *data);
int		check_texture(char *line, t_data *data);
int		get_texture(char *line, char **path);
int		get_color(char *line, t_color *element);
int		extract_one_color(int *i, char *line, int *color_element);
int		go_next_color(int *i, char **line);
int		get_raw_map(char **line, int fd, t_lst **raw_map);
int		empty_line(char *line);
int		valid_line(char *line);

int		add_node(char *line, t_lst	**lst);
void	free_lst(t_lst *lst);
void	free_get_next_line(int fd, char **line);
//void	delete_node(t_lst **lst);
int		parsing(char *filename, t_data *data);
void	err_parsing(char **line, int fd, t_data *data);

#endif