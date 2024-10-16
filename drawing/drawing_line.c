/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:20:53 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 22:27:36 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_line(t_data *data, int x_final, int y_final, int color)
{
	int	dx;
	int	dy;

	dx = x_final - (data->player.x * PIXELS_PER_CELL);
	dy = y_final - (data->player.y * PIXELS_PER_CELL);
	if (abs(dx) > abs(dy))
		draw_gradual(data, dx, dy, color);
	else
		draw_steep(data, dx, dy, color);
	//printf("px : %i, py : %i\n", (int)(data->player.x * PIXELS_PER_CELL), (int)(data->player.y * PIXELS_PER_CELL));
}

void	draw_gradual(t_data *data, int dx, int dy, int color)
{
	int	d;
	int	i;
	int	px;
	int	py;

	i = 0;
	d = 2 * abs(dy) - abs(dx);
	px = (data->player.x * PIXELS_PER_CELL);
	py = (data->player.y * PIXELS_PER_CELL);
	draw_pixel(&(data)->minimap, px, py, color);
	while (i < abs(dx))
	{
		if (dx > 0)
			px += 1;
		else
			px -= 1;
		if (d < 0)
			d = d + (2 * abs(dy));
		else 
		{
			if (dy > 0)
				py += 1;
			else
				py -= 1;
			d = d + (2 * abs(dy)) - (2 * abs(dx));
		}
		draw_pixel(&(data)->minimap, px, py, color);
		i++;
	}
}

void	draw_steep(t_data *data, int dx, int dy, int color)
{
	int	d;
	int	i;
	int	px;
	int	py;

	i = 0;
	d = 2 * abs(dx) - abs(dy);
	px = (data->player.x * PIXELS_PER_CELL);
	py = (data->player.y * PIXELS_PER_CELL);
	draw_pixel(&(data)->minimap, px, py, color);
	while (i < abs(dy))
	{
		if (dy > 0)
			py += 1;
		else
			py -= 1;
		if (d < 0)
			d = d + (2 * abs(dx));
		else
		{
			if (dx > 0)
				px += 1;
			else
				px -= 1;
			d = d + (2 * abs(dx)) - (2 * abs(dy));
		}
		draw_pixel(&(data)->minimap, px, py, color);
		i++;
	}
}
