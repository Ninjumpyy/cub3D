/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:58:06 by thomas            #+#    #+#             */
/*   Updated: 2024/10/25 13:04:27 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	parsing_file(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	t_lst	*map_lst;

	map_lst = NULL;
	check_fd(&fd, filename);
	ft_memset(&data->env, 0, sizeof(t_env));
	parse_texture_color(&line, fd, data);
	if (!get_map_lst(&line, fd, &map_lst))
		err_parsing(&line, fd, data, &map_lst);
	parse_map(&line, fd, &map_lst, data);
	close(fd);
}

void	parse_texture_color(char **line, int fd, t_data *data)
{
	int	nb_elem;
	int	res;

	nb_elem = 0;
	*line = get_next_line(fd);
	while (nb_elem < 6 && *line != NULL)
	{
		res = check_elem(*line, &data->env);
		if (res == -1)
			err_parsing(line, fd, data, NULL);
		else
			nb_elem += res;
		free(*line);
		*line = get_next_line(fd);
	}
	if (nb_elem != 6)
		err_parsing(line, fd, data, NULL);
}

void	parse_map(char **line, int fd, t_lst **map_lst, t_data *data)
{
	t_lst	*ptr;

	ptr = *map_lst;
	if (!check_map(&ptr, &data->map_width, &data->map_height, data))
		err_parsing(line, fd, data, map_lst);
	data->env.map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (data->env.map == NULL)
		err_parsing(line, fd, data, map_lst);
	if (!create_map(map_lst, data))
		err_parsing(line, fd, data, map_lst);
	if (!map_closed(data->env.map, data->map_width, data->map_height))
		err_parsing(line, fd, data, map_lst);
}
