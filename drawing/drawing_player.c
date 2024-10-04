/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:09:29 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 17:43:01 by thomas           ###   ########.fr       */
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
}
