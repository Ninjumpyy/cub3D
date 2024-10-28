/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:00:03 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 12:00:22 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_elem(char *line, t_env *env)
{
	int	res;

	while (*line == ' ')
		line++;
	if (*line == '\n' || *line == '\0')
		return (0);
	res = check_texture(line, env);
	if (res != 2)
		return (res);
	res = check_color(line, env);
	return (res);
}

int	check_texture(char *line, t_env *env)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (env->no_texture != NULL || !get_texture(line, &env->no_texture))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (env->so_texture != NULL || !get_texture(line, &env->so_texture))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (env->we_texture != NULL || !get_texture(line, &env->we_texture))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (env->ea_texture != NULL || !get_texture(line, &env->ea_texture))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "DO ", 3) == 0)
	{
		if (env->door_texture != NULL || !get_texture(line, &env->door_texture))
			return (-1);
		return (0);
	}
	return (2);
}

int	get_texture(char *line, char **path)
{
	int		i;
	int		fd;
	char	*texture;

	i = 0;
	line += 2;
	while (*line == ' ')
		line++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
		i++;
	texture = ft_substr(line, 0, i);
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (free(texture), 0);
	*path = texture;
	fd = open(texture, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_color(char *line, t_env *env)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (env->floor.is_set || !get_color(line, &env->floor))
		{
			printf("prob color f\n");
			return (-1);
		}
		env->floor.is_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (env->ceiling.is_set || !get_color(line, &env->ceiling))
		{
			printf("prob color c\n");
			return (-1);
		}
		env->ceiling.is_set = 1;
		return (1);
	}
	return (-1);
}

int	get_color(char *line, t_color *elem)
{
	int	i;

	i = 0;
	line++;
	while (*line == ' ')
		line++;
	if (!extract_one_color(&i, line, &elem->r))
		return (0);
	if (go_next_color(&i, &line))
		return (0);
	if (!extract_one_color(&i, line, &elem->g))
		return (0);
	if (go_next_color(&i, &line))
		return (0);
	if (!extract_one_color(&i, line, &elem->b))
		return (0);
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (0);
	return (1);
}
