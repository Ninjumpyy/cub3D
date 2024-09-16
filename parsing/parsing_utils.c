/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:19:17 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/16 12:43:15 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_fd(int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		if (write(2, "Error: can't open .cub file...\n", 31) == -1)
			exit(1);
		exit (1);
	}
}

void	init_data(t_map_spec *map_data)
{
	map_data->no = NULL;
	map_data->so = NULL;
	map_data->we = NULL;
	map_data->ea = NULL;
	map_data->floor.flag = 0;
	map_data->ceiling.flag = 0;
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
