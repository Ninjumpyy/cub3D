/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:20:53 by thomas            #+#    #+#             */
/*   Updated: 2024/10/23 16:29:33 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
/*
void draw_line(t_data *data, float x_final, float y_final, int color)
{
    int x_start = (data->player.x * PIXELS_PER_CELL) - data->player.offset_x;
    int y_start = (data->player.y * PIXELS_PER_CELL) - data->player.offset_y;
    int x_end = (x_final) - data->player.offset_x;
    int y_end = (y_final) - data->player.offset_y;

    int dx = x_end - x_start;
    int dy = y_end - y_start;

    if (abs(dx) > abs(dy))
        draw_gradual(data, x_start, y_start, x_end, y_end, color);
    else
        draw_steep(data, x_start, y_start, x_end, y_end, color);
}

void draw_gradual(t_data *data, int x_start, int y_start, int x_end, int y_end, int color)
{
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int xi = (dx > 0) ? 1 : -1;
    dx = abs(dx);
    int yi = (dy > 0) ? 1 : -1;
    dy = abs(dy);
    int D = 2 * dy - dx;
    int y = y_start;

    for (int x = x_start; x != x_end; x += xi)
    {
        if (x >= 0 && x < MINIMAP_WIDTH && y >= 0 && y < MINIMAP_HEIGHT)
            draw_pixel(&(data->minimap), x, y, color);

        if (D > 0)
        {
            y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void draw_steep(t_data *data, int x_start, int y_start, int x_end, int y_end, int color)
{
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int xi = (dx > 0) ? 1 : -1;
    dx = abs(dx);
    int yi = (dy > 0) ? 1 : -1;
    dy = abs(dy);
    int D = 2 * dx - dy;
    int x = x_start;

    for (int y = y_start; y != y_end; y += yi)
    {
        if (y >= 0 && y < MINIMAP_HEIGHT && x >= 0 && x < MINIMAP_WIDTH)
            draw_pixel(&(data->minimap), x, y, color);

        if (D > 0)
        {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}*/



void	draw_line(t_data *data, float x_final, float y_final, int color)
{
	int	dx;
	int	dy;

	dx = (int)(x_final - (data->player.x * PIXELS_PER_CELL));
	dy = (int)(y_final - (data->player.y * PIXELS_PER_CELL));
	if (abs(dx) > abs(dy))
		draw_gradual(data, dx, dy, color);
	else
		draw_steep(data, dx, dy, color);
}

void	draw_gradual(t_data *data, int dx, int dy, int color)
{
	int	d;
	int	i;
	int	px;
	int	py;

	i = 0;
	d = 2 * abs(dy) - abs(dx);
	px = (data->player.x * PIXELS_PER_CELL) - data->player.offset_x;
	py = (data->player.y * PIXELS_PER_CELL) - data->player.offset_y;
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
		if (px >= 0 && px < MINIMAP_WIDTH && py >= 0 && py < MINIMAP_HEIGHT)
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
	px = (data->player.x * PIXELS_PER_CELL) - data->player.offset_x;
	py = (data->player.y * PIXELS_PER_CELL) - data->player.offset_y;
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
		if (px >= 0 && px < MINIMAP_WIDTH && py >= 0 && py < MINIMAP_HEIGHT)
			draw_pixel(&(data)->minimap, px, py, color);
		i++;
	}
}
