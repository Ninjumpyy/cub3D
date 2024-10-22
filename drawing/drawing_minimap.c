/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:06:13 by thomas            #+#    #+#             */
/*   Updated: 2024/10/22 16:35:04 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	y_start;
	int	y_end;
	int	x_start;
	int	x_end;

	if (data->map_height * PIXELS_PER_CELL < MINIMAP_HEIGHT)
	{
		y_start = 0;
		y_end = data->map_height * PIXELS_PER_CELL;
	}
	else
	{
		if (((data->player.y * PIXELS_PER_CELL) + (MINIMAP_HEIGHT / 2)) > (data->map_height * PIXELS_PER_CELL))
			y_end = data->map_height * PIXELS_PER_CELL;
		else if (((data->player.y * PIXELS_PER_CELL) - (MINIMAP_HEIGHT / 2)) < 0)
			y_end = MINIMAP_HEIGHT;
		else
			y_end = (data->player.y * PIXELS_PER_CELL) + (MINIMAP_HEIGHT / 2);
		y_start = y_end - MINIMAP_HEIGHT;
	}
	if (data->map_width * PIXELS_PER_CELL < MINIMAP_WIDTH)
	{
		x_start = 0;
		x_end = data->map_width * PIXELS_PER_CELL;
	}
	else
	{
		if (((data->player.x * PIXELS_PER_CELL) + (MINIMAP_WIDTH / 2)) > (data->map_width * PIXELS_PER_CELL))
			x_end = data->map_width * PIXELS_PER_CELL;
		else if (((data->player.x * PIXELS_PER_CELL) - (MINIMAP_WIDTH / 2)) < 0)
			x_end = MINIMAP_WIDTH;
		else
			x_end = (data->player.x * PIXELS_PER_CELL) + (MINIMAP_WIDTH / 2);
		x_start = x_end - MINIMAP_WIDTH;
	}
	y = y_start;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			draw_pixel(&(data)->minimap, (x - x_start), (y - y_start), find_cell_color(x, y, data));
			x++;
		}
		y++;
	}

	//draw_grid(data);
	draw_player(data, x_start, y_start);
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
			draw_pixel(&(data)->minimap, x, y, convert_color(122, 192, 192, 192));
			draw_pixel(&(data)->minimap, y, x, convert_color(122, 192, 192, 192));
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
		return(convert_color(122, 180, 180, 180));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(122, 180, 180, 180));
	else
		return(convert_color(122, 0, 0, 0));
}

void	draw_player(t_data *data, int x_start, int y_start)
{
	float	px;
	float	py;
	int		i;
	int		j;

	px = (data->player.x * PIXELS_PER_CELL) - x_start - (SIZE_PIXEL_PLAYER / 2);
	py = (data->player.y * PIXELS_PER_CELL) - y_start - (SIZE_PIXEL_PLAYER / 2);
	j = 0;
	while (j < SIZE_PIXEL_PLAYER)
	{
		i = 0;
		while (i < SIZE_PIXEL_PLAYER)
		{
			draw_pixel(&(data)->minimap, (int)px + i, (int)py + j, convert_color(122, 255, 255, 0));
			i++;
		}
		j++;
	}
	draw_line(data, (data->player.x * PIXELS_PER_CELL) + (cos(data->player.angle) * LINE_LENGTH), (data->player.y * PIXELS_PER_CELL) + (-sin(data->player.angle) * LINE_LENGTH), convert_color(122, 255, 255, 0));
}
