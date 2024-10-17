/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:36 by thomas            #+#    #+#             */
/*   Updated: 2024/10/17 15:50:01 by tle-moel         ###   ########.fr       */
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

void	redraw_minimap(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_ceiling(data);
	draw_floor(data);
	draw_minimap(data);
	draw_player(data);
	cast_rays(data);
	draw_crosshair(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->cub.img, 512, 0);
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
