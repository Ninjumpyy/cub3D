/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:19:17 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/11 18:08:18 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	/*
	data->map = NULL;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->img = NULL;
	data->addr = NULL;*/
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
