/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:01:42 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/17 16:02:29 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_minimap(t_data *data, int player_x, int player_y)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	start_x = player_x - (VIEWPORT_CELLS / 2);
	start_y = player_y - (VIEWPORT_CELLS / 2);
	if (start_x + VIEWPORT_CELLS > data->map_data->width)
		start_x = data->map_data->width - VIEWPORT_CELLS;
	if (start_y + VIEWPORT_CELLS > data->map_data->height)
		start_y = data->map_data->height - VIEWPORT_CELLS;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	y = 0;
	while (y < VIEWPORT_CELLS)
	{
		x = 0;
		while (x < VIEWPORT_CELLS)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			draw_cell(data, map_x, map_y);
			x++;
		}
		y++;
	}
}

void	draw_cell(t_data *data, int map_x, int map_y)
{
	int	i;
	int	j;
	int color;

	if (map_x > data->map_data->width - 1 || map_y > data->map_data->height - 1)
		color = convert_color(169, 169, 169);
	else if (data->map_data->map[map_y][map_x] == ' ' || data->map_data->map[map_y][map_x] == '\0' || data->map_data->map[map_y][map_x] == '\n')
		color = convert_color(169, 169, 169);
	else if (data->map_data->map[map_y][map_x] == '1')
		color = convert_color(250, 250, 250);
	else
		color = convert_color(0, 0, 0);
	j = 0;
	while (j < CELL_SIZE)
	{
		i = 0;
		while (i < CELL_SIZE)
		{
			draw_pixel(&(data)->minimap, (map_x * CELL_SIZE) + i, (map_y * CELL_SIZE) + j, color);
			i++;
		}
		j++;
	}
}
