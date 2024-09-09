/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:19:17 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/09 13:35:27 by tle-moel         ###   ########.fr       */
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
	write(2, "Error: .cub file\n", 18);
		exit(1);
	exit(1);
}

void	err_map(t_lst *raw_map, t_data *data)
{
	free_data(data);
	free_lst(raw_map);
	if (write(2, "Error: .cub file\n", 18) == -1)
		exit(1);
	exit(1);
}

void	check_fd(int fd)
{
	if (fd == -1)
	{
		if (write(2, "Error: can't open .cub file...\n", 31) == -1)
			exit(1);
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
		free_map(data->map);
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
