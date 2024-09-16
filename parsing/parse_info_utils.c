/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:31:04 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/11 17:57:37 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_info(char *line, t_data *data)
{
	int	res;

	while (*line == ' ')
		line++;
	if (*line == '\n' || *line == '\0')
		return (0);
	res = check_texture(line, data);
	if (res != 0)
		return (res);
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (data->floor.flag || get_color(line, &data->floor))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (data->ceiling.flag || get_color(line, &data->ceiling))
			return (-1);
		return (1);
	}
	return (-1);
}

int	check_texture(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (data->no != NULL || get_texture(line, &data->no))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (data->so != NULL || get_texture(line, &data->so))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (data->we != NULL || get_texture(line, &data->we))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (data->ea != NULL || get_texture(line, &data->ea))
			return (-1);
		return (1);
	}
	return (0);
}

int	get_texture(char *line, char **path)
{
	int		i;
	char	*info;
	int		fd;

	i = 0;
	line += 2;
	while (*line == ' ')
		line++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		i++;
	info = ft_substr(line, 0, i);
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (free(info), 1);
	*path = info;
	fd = open(info, O_RDONLY);
	if (fd == -1)
		return (1);
	fd = close(fd);
	return (0);
}

int	get_color(char *line, t_color *element)
{
	int		i;

	i = 0;
	line++;
	while (*line == ' ')
		line++;
	if (extract_one_color(&i, line, &element->r))
		return (1);
	if (go_next_color(&i, &line))
		return (1);
	if (extract_one_color(&i, line, &element->g))
		return (1);
	if (go_next_color(&i, &line))
		return (1);
	if (extract_one_color(&i, line, &element->b))
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (1);
	return (0);
}

int	extract_one_color(int *i, char *line, int *color_element)
{
	char	*color;

	if (!ft_isdigit(line[*i]))
		return (1);
	while (ft_isdigit(line[*i]) && *i < 4)
		(*i)++;
	if (line[*i] != ' ' && line[*i] != ',' && line[*i] != '\n' && \
	line[*i] != '\0')
		return (1);
	color = ft_substr(line, 0, *i);
	*color_element = ft_atoi(color);
	free(color);
	if (*color_element > 255)
		return (1);
	return (0);
}
