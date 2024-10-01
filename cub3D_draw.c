/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:50:07 by thomas            #+#    #+#             */
/*   Updated: 2024/10/01 14:44:10 by tle-moel         ###   ########.fr       */
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
}
