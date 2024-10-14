/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:36 by thomas            #+#    #+#             */
/*   Updated: 2024/10/14 16:14:22 by rpandipe         ###   ########.fr       */
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

void	draw_crosshair(t_data *data)
{
	int	i;

	i = -CROSSHAIR_LEN;
	while (i < CROSSHAIR_LEN)
	{
		draw_pixel(&(data)->cub, data->player.mouse_x + i, data->player.mouse_y, CROSSHAIR_COLOR);
		i++;
	}
	i = -CROSSHAIR_LEN;
	while (i < CROSSHAIR_LEN)
	{
		draw_pixel(&(data)->cub, data->player.mouse_x, data->player.mouse_y + i, CROSSHAIR_COLOR);
		i++;
	}
}
