/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:06:13 by thomas            #+#    #+#             */
/*   Updated: 2024/10/25 13:09:03 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	determine_y_offset(t_data *data, int *y_end)
{
	if (data->map_height * PIXELS_PER_CELL < MINIMAP_HEIGHT)
	{
		data->player.offset_y = 0;
		*y_end = data->map_height * PIXELS_PER_CELL;
	}
	else
	{
		if (((data->player.y * PIXELS_PER_CELL) + (MINIMAP_HEIGHT / 2)) > (data->map_height * PIXELS_PER_CELL))
			*y_end = data->map_height * PIXELS_PER_CELL;
		else if (((data->player.y * PIXELS_PER_CELL) - (MINIMAP_HEIGHT / 2)) < 0)
			*y_end = MINIMAP_HEIGHT;
		else
			*y_end = (data->player.y * PIXELS_PER_CELL) + (MINIMAP_HEIGHT / 2);
		data->player.offset_y = *y_end - MINIMAP_HEIGHT;
	}
}

void	determine_x_offset(t_data *data, int *x_end)
{
	if (data->map_width * PIXELS_PER_CELL < MINIMAP_WIDTH)
	{
		data->player.offset_x = 0;
		*x_end = data->map_width * PIXELS_PER_CELL;
	}
	else
	{
		if (((data->player.x * PIXELS_PER_CELL) + (MINIMAP_WIDTH / 2)) > (data->map_width * PIXELS_PER_CELL))
			*x_end = data->map_width * PIXELS_PER_CELL;
		else if (((data->player.x * PIXELS_PER_CELL) - (MINIMAP_WIDTH / 2)) < 0)
			*x_end = MINIMAP_WIDTH;
		else
			*x_end = (data->player.x * PIXELS_PER_CELL) + (MINIMAP_WIDTH / 2);
		data->player.offset_x = *x_end - MINIMAP_WIDTH;
	}
}

void	draw_minimap_on_cub(t_data *data)
{
	int	x;
	int	y;
	int	y_end;
	int	x_end;

	determine_y_offset(data, &y_end);
	determine_x_offset(data, &x_end);
	y = data->player.offset_y;
	while (y < y_end)
	{
		x = data->player.offset_x;
		while (x < x_end)
		{
			draw_pixel(&(data)->minimap, (x - data->player.offset_x), (y - data->player.offset_y), find_cell_color(x, y, data));
			x++;
		}
		y++;
	}
	draw_player(data);
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	y_end;
	int	x_end;

	determine_y_offset(data, &y_end);
	determine_x_offset(data, &x_end);
	y = data->player.offset_y;
	while (y < y_end)
	{
		x = data->player.offset_x;
		while (x < x_end)
		{
			draw_pixel(&(data)->minimap, (x - data->player.offset_x), (y - data->player.offset_y), find_cell_color(x, y, data));
			x++;
		}
		y++;
	}
	draw_player(data);
}

int	find_cell_color(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / PIXELS_PER_CELL;
	map_y = y / PIXELS_PER_CELL;
	if (data->env.map[map_y][map_x] == '1')
		return(convert_color(122, 242, 242, 242));
	else if (data->env.map[map_y][map_x] == '2')
		return(convert_color(122, 133, 255, 77));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(122, 242, 242, 242));
	else
		return(convert_color(122, 38, 38, 38));
}

