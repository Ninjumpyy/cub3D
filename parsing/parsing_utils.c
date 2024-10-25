/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:05:52 by thomas            #+#    #+#             */
/*   Updated: 2024/10/25 11:30:43 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_fd(int *fd, char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_error("Error\nCan't open .cub file...\n");
		exit(EXIT_FAILURE);
	}
}

int	extract_one_color(int *i, char *line, int *color_elem)
{
	char	*color;

	if (!ft_isdigit(line[*i]))
		return (0);
	while (ft_isdigit(line[*i]) && *i < 4)
		(*i)++;
	if (line[*i] != ' ' && line[*i] != ',' && line[*i] != '\n' && \
	line[*i] != '\0')
		return (0);
	color = ft_substr(line, 0, *i);
	*color_elem = ft_atoi(color);
	free(color);
	if (*color_elem > 255 || *color_elem < 0)
		return (0);
	return (1);
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
	line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == '2')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (0);
	return (1);
}
