/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:36:47 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/30 16:36:28 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_lst	*raw_map;

	fd = open(filename, O_RDONLY);
	check_fd(fd);
	init_data(data);
	parse_info(&line, fd, data);
	raw_map = NULL;
	if (get_raw_map(&line, fd, &raw_map))
	{
		free_lst(raw_map);
		err_parsing(&line, fd, data);
	}
	//parse_map();
	return (0);
}

void	parse_info(char **line, int fd, t_data *data)
{
	int		info;
	int		i;

	info = 0;
	*line = get_next_line(fd);
	while (info < 6 && *line != NULL)
	{
		i = check_info(*line, data);
		if (i == -1)
			err_parsing(line, fd, data);
		else
			info += i;
		free(*line);
		*line = get_next_line(fd);
	}
	if (info != 6)
		err_parsing(line, fd, data);
}
