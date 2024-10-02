/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:50:07 by thomas            #+#    #+#             */
/*   Updated: 2024/10/02 19:08:26 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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
			draw_pixel(&(data)->minimap, x, y, find_color(x, y, data));
			x++;
		}
		y++;
	}
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

void	draw_player(t_data *data)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = (data->player.x * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	player_y = (data->player.y * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	j = 0;
	while (j < SIZE_PIXEL_PLAYER)
	{
		i = 0;
		while (i < SIZE_PIXEL_PLAYER)
		{
			draw_pixel(&(data)->minimap, player_x + i, player_y + j, convert_color(255, 255, 0));
			i++;
		}
		j++;
	}
	//draw_player_orientation(data);
	draw_line(data);
}

void	draw_player_orientation(t_data *data)
{
	float 	line_x;
	float	line_y;
	int		i;

	i = 0;
	//printf("player_x : %f, player_y : %f\n", data->player.x, data->player.y);
	//printf("pix_x : %f, pix_y : %f\n", data->player.x * PIXELS_PER_CELL, data->player.y * PIXELS_PER_CELL);
	while (i < 10)
	{
		line_x = (data->player.x * PIXELS_PER_CELL) + cos(data->player.angle) * (i * CELLS_PER_PIXEL);
		line_y = (data->player.y * PIXELS_PER_CELL) - sin(data->player.angle) * (i * CELLS_PER_PIXEL);
		//printf("line_x : %f, line_y : %f\n", line_x, line_y);
		draw_pixel(&(data)->minimap, line_x, line_y, convert_color(255, 0, 0));
		i++;
	}
}

void	draw_line(t_data *data)
{
	int		line_length;
	float	x_start;
	float	y_start;
	float	x_end;
	float	y_end;
	float	dx;
	float	dy;
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;
	int		i;
	int		xi;
	int		yi;

	line_length = 50;
	x_start = (data->player.x * PIXELS_PER_CELL);
	y_start = (data->player.y * PIXELS_PER_CELL);
	x_end = (data->player.x * PIXELS_PER_CELL) + cos(data->player.angle) * line_length;
	y_end = (data->player.y * PIXELS_PER_CELL) - sin(data->player.angle) * line_length;
	dx = x_end - x_start;
	dy = y_end - y_start;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	
	x_increment = dx / steps;
	y_increment = dy / steps;

	x = x_start;
	y = y_start;

	i = 0;
	while (i < steps)
	{
		xi = (int)x;
		yi = (int)y;
		
		printf("xi : %i, yi : %i\n", xi, yi);
		if (xi >= 0 && xi < MINIMAP_WIDTH && yi >= 0 && yi < MINIMAP_HEIGHT)
			draw_pixel(&(data)->minimap, xi, yi, convert_color(255, 255, 0));
		
		x += x_increment;
		y += y_increment;
		i++;
	}
}
