/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:50:07 by thomas            #+#    #+#             */
/*   Updated: 2024/09/30 18:28:48 by thomas           ###   ########.fr       */
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

	y = 32;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			draw_pixel(&(data)->minimap, x, y, convert_color(220, 220, 220));
			draw_pixel(&(data)->minimap, y, x, convert_color(220, 220, 220));
			x++;
		}
		y += 32;
	}
}
