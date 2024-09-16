/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:36:47 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:34 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	parsing(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_lst	*raw_map;
	t_map_spec	*map_data;

	check_fd(&fd, filename);
	map_data = malloc(sizeof(t_map_spec));
	if (map_data == NULL)
		err_malloc(fd);
	init_data(map_data);
	parse_info(&line, fd, map_data);
	raw_map = NULL;
	if (get_raw_map(&line, fd, &raw_map))
	{
		free_lst(raw_map);
		err_parsing(&line, fd, map_data);
	}
	close(fd);
	parse_map(raw_map, map_data);
	data->map_data = map_data;
}

void	parse_info(char **line, int fd, t_map_spec *map_data)
{
	int		info;
	int		i;

	info = 0;
	*line = get_next_line(fd);
	while (info < 6 && *line != NULL)
	{
		i = check_info(*line, map_data);
		if (i == -1)
			err_parsing(line, fd, map_data);
		else
			info += i;
		free(*line);
		*line = get_next_line(fd);
	}
	if (info != 6)
		err_parsing(line, fd, map_data);
}

void	parse_map(t_lst *raw_map, t_map_spec *map_data)
{
	int			width;
	int			height;
	t_lst		*ptr;

	width = 0;
	height = 0;
	ptr = raw_map;
	if (check_map(&ptr, &width, &height, map_data))
		err_map(raw_map, map_data);
	map_data->map = ft_calloc((height + 1), sizeof(char *));
	if (map_data->map == NULL)
		err_map(raw_map, map_data);
	create_map(raw_map, map_data);
	if (!map_closed(map_data->map, width, height))
	{
		free_map_data(map_data);
		free(map_data);
		if (write(2, "Error: .cub file\n", 18) == -1)
			exit(1);
		exit(1);
	}
}
