/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:06:13 by thomas            #+#    #+#             */
/*   Updated: 2024/10/23 14:35:46 by tle-moel         ###   ########.fr       */
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
		return(convert_color(122, 180, 180, 180));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(122, 180, 180, 180));
	else
		return(convert_color(122, 0, 0, 0));
}

void	draw_player(t_data *data)
{
	float	px;
	float	py;
	int		i;
	int		j;

	px = (data->player.x * PIXELS_PER_CELL) - data->player.offset_x - (SIZE_PIXEL_PLAYER / 2);
	py = (data->player.y * PIXELS_PER_CELL) - data->player.offset_y - (SIZE_PIXEL_PLAYER / 2);
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
	//draw_line(data, (data->player.x * PIXELS_PER_CELL) + (cos(data->player.angle) * LINE_LENGTH), (data->player.y * PIXELS_PER_CELL) + (-sin(data->player.angle) * LINE_LENGTH), convert_color(122, 255, 255, 0));
}
