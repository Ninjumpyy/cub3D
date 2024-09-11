/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:59 by thomas            #+#    #+#             */
/*   Updated: 2024/09/11 17:57:37 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_player(t_player *player)
{
	player->flag = 0;
	player->x = -1;
	player->y = -1;
}

int	check_map(t_lst **ptr, int *width, t_player *player, int *height)
{
	while (*ptr)
	{
		if (check_player_and_width((*ptr)->line, width, player, *height))
			return (1);
		(*height)++;
		*ptr = (*ptr)->next;
	}
	return (0);
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
			if (player->flag == 1)
				return (1);
			player->flag = 1;
			player->x = i;
			player->y = curr_height;
		}
		i++;
	}
	if (i > *width)
		*width = i;
	return (0);
}

void	create_map(t_lst *raw_map, t_data *data)
{
	t_lst	*ptr;
	int		i;
	int		len;

	i = 0;
	ptr = raw_map;
	while (ptr)
	{
		len = ft_strlen(ptr->line);
		data->map[i] = malloc((len + 1) * sizeof(char));
		if (data->map[i] == NULL)
			err_map(raw_map, data);
		ft_strlcpy(data->map[i], ptr->line, len + 1);
		ptr = ptr->next;
		i++;
	}
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
			map[y][x] == 'W' || map[y][x] == 'E')
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
