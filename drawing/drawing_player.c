/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:09:29 by thomas            #+#    #+#             */
/*   Updated: 2024/10/16 12:59:47 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player(t_data *data)
{
	float	px;
	float	py;
	int		i;
	int		j;

	px = (data->player.x * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	py = (data->player.y * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	j = 0;
	while (j < SIZE_PIXEL_PLAYER)
	{
		i = 0;
		while (i < SIZE_PIXEL_PLAYER)
		{
			draw_pixel(&(data)->minimap, (int)px + i, (int)py + j, convert_color(255, 255, 0));
			i++;
		}
		j++;
	}
	draw_line(data, (data->player.x * PIXELS_PER_CELL) + (cos(data->player.angle) * LINE_LENGTH), (data->player.y * PIXELS_PER_CELL) + (-sin(data->player.angle) * LINE_LENGTH), convert_color(255, 255, 0));
	data->player.sprite.x = (CUB_WIDTH - data->player.sprite.img.width) / 2;
	data->player.sprite.y = CUB_HEIGHT - data->player.sprite.img.height;
	printf("Player sprite drawn at: x = %f, y = %f, CUB_WIDTH = %d, val = %d\n", data->player.sprite.x, data->player.sprite.y, CUB_WIDTH, data->player.sprite.img.width);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->player.sprite.img.img, data->player.sprite.x, data->player.sprite.y);
}
