/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:19:17 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/30 16:56:51 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	err_parsing(char **line, int fd, t_data *data)
{
	free_get_next_line(fd, line);
	free_data(data);
	if (*line)
		free(*line);
	close(fd);
	write(2, "Error: .cub file\n", 21);
	exit(1);
}

void	check_fd(int fd)
{
	if (fd == -1)
	{
		write(2, "Error: can't open .cub file...\n", 31);
		exit (1);
	}
}

void	init_data(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor.flag = 0;
	data->ceiling.flag = 0;
	data->map = NULL;
}

void	free_data(t_data *data)
{
	if (data->no)
	{
		free(data->no);
		data->no = NULL;
	}
	if (data->so)
	{
		free(data->so);
		data->so = NULL;
	}
	if (data->we)
	{
		free(data->we);
		data->we = NULL;
	}
	if (data->ea)
	{
		free(data->ea);
		data->ea = NULL;
	}
	if (data->map)
	{
		free(data->map);
		data->map = NULL;
	}
}

int	go_next_color(int *i, char **line)
{
	while ((*line)[*i] == ' ')
			(*i)++;
	if ((*line)[*i] != ',')
		return (1);
	(*i)++;
	while ((*line)[*i] == ' ')
		(*i)++;
	*line += *i;
	*i = 0;
	return (0);
}
