/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:36:47 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/11 17:57:48 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	close(fd);
	parse_map(raw_map, data);
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

void	parse_map(t_lst *raw_map, t_data *data)
{
	int			width;
	int			height;
	t_player	player;
	t_lst		*ptr;

	width = 0;
	height = 0;
	init_player(&player);
	ptr = raw_map;
	if (check_map(&ptr, &width, &player, &height))
		err_map(raw_map, data);
	if (player.flag == 0)
		err_map(raw_map, data);
	data->map = ft_calloc((height + 1), sizeof(char *));
	if (data->map == NULL)
		err_map(raw_map, data);
	create_map(raw_map, data);
	free_lst(raw_map);
	if (!map_closed(data->map, width, height))
	{
		free_data(data);
		if (write(2, "Error: .cub file\n", 18) == -1)
			exit(1);
		exit(1);
	}
}
