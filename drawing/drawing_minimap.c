/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:06:13 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 16:12:17 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			draw_pixel(&(data)->minimap, x, y, find_cell_color(x, y, data));
			x++;
		}
		y++;
	}
	draw_grid(data);
}

void	draw_grid(t_data *data)
{
	int	x;
	int	y;

	y = PIXELS_PER_CELL;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			draw_pixel(&(data)->minimap, x, y, convert_color(220, 220, 220));
			draw_pixel(&(data)->minimap, y, x, convert_color(220, 220, 220));
			x++;
		}
		y += PIXELS_PER_CELL;
	}
}

int	find_cell_color(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / PIXELS_PER_CELL;
	map_y = y / PIXELS_PER_CELL;
	if (data->env.map[map_y][map_x] == '1')
		return(convert_color(250, 250, 250));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(169, 169, 169));
	else
		return(convert_color(0, 0, 0));
}

