/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:11:18 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 11:58:34 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_map(t_lst **ptr, int *width, int *height, t_data *data)
{
	while (*ptr)
	{
		if (!check_player_and_width((*ptr)->line, width,
				&data->player, *height))
			return (0);
		(*height)++;
		*ptr = (*ptr)->next;
	}
	if (data->player.is_found == 0)
		return (0);
	return (1);
}

float	init_player_angle(char *line, int i)
{
	if (line[i] == 'N')
		return (PI / 2);
	else if (line[i] == 'S')
		return ((3 * PI) / 2);
	else if (line[i] == 'W')
		return (PI);
	else
		return (0.0);
}

int	check_player_and_width(char *line, int *width, t_player *player, \
int curr_height)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' || \
		line[i] == 'E' || line[i] == 'W')
		{
			if (player->is_found == 1)
				return (0);
			player->is_found = 1;
			player->x = (float)i + 0.5;
			player->y = (float)curr_height + 0.5;
			player->angle = init_player_angle(line, i);
		}
		i++;
	}
	if (i > *width)
		*width = i;
	return (1);
}

int	create_map(t_lst **map_lst, t_data *data)
{
	t_lst	*ptr;
	int		i;
	int		len;

	i = 0;
	ptr = *map_lst;
	while (ptr)
	{
		len = ft_strlen(ptr->line);
		data->env.map[i] = ft_calloc((data->map_width + 2), sizeof(char));
		if (data->env.map[i] == NULL)
			return (0);
		ft_strlcpy(data->env.map[i], ptr->line, len + 1);
		ptr = ptr->next;
		i++;
	}
	free_lst(map_lst);
	return (1);
}

int	map_closed(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || \
			map[y][x] == 'W' || map[y][x] == 'E' || map[y][x] == '2')
			{
				if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
					return (0);
				else if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || \
				map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || \
				map[y - 1][x] == '\n' || map[y + 1][x] == '\n' || \
				map[y][x - 1] == '\n' || map[y][x + 1] == '\n')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
