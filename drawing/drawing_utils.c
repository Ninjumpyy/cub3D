/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:36 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 16:14:00 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	convert_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_line(t_data *data, float x_increment, float y_increment, int steps)
{
	float	x;
	float	y;
	int		i;

	x = data->player.x * PIXELS_PER_CELL;
	y = data->player.y * PIXELS_PER_CELL;
	i = 0;
	while (i < steps)
	{
		if ((int)x >= 0 && (int)x < MINIMAP_WIDTH && (int)y >= 0 && (int)y < MINIMAP_HEIGHT)
			draw_pixel(&(data)->minimap, (int)x, (int)y, convert_color(255, 255, 0));
		
		x += x_increment;
		y += y_increment;
		i++;
	}
}

void	draw_line_bresenham(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		draw_pixel(&(data)->minimap, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
