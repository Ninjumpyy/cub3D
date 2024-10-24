/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:36 by thomas            #+#    #+#             */
/*   Updated: 2024/10/24 06:04:25 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	/*if (x < 0 || x >= img->width || y < 0 || y >= img->height)
	{
		printf("Out of bounds\n");
		return ;
	}*/
	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	convert_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	redraw_minimap(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	draw_background(data);
	draw_cub_scene(data);
	draw_minimap(data);
	draw_crosshair(data);
	draw_player_sprite(data);
	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->cub.img, 0, 0);
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

void	normalize_angle(t_ray *ray)
{
	if (ray->angle < 0)
		ray->angle += (2 * PI);
	if (ray->angle > 2 * PI)
		ray->angle -= (2 * PI);
}
