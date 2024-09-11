/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:56:27 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/11 17:57:38 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_raw_map(char **line, int fd, t_lst **raw_map)
{
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (*line == NULL)
		return (1);
	while (*line)
	{
		if (!valid_line(*line))
			return (1);
		if (empty_line(*line))
			break ;
		add_node(*line, raw_map);
		*line = get_next_line(fd);
	}
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (*line != NULL)
		return (1);
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

int	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '0' || line[i] == '1' || \
	line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (0);
	return (1);
}
