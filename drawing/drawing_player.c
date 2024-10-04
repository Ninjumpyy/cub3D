/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:09:29 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 16:10:20 by thomas           ###   ########.fr       */
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
	draw_player_orientation(data, (cos(data->player.angle) * LINE_LENGTH), (-sin(data->player.angle) * LINE_LENGTH));
}

/*
void	draw_player_orientation(t_data *data, float dx, float dy)
{
	//float	dx;
	//float	dy;
	int		steps;
	float	x_increment;
	float	y_increment;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_increment = dx / steps;
	y_increment = dy / steps;
	draw_line(data, x_increment, y_increment, steps);
}*/

void	draw_player_orientation(t_data *data, float dx, float dy)
{
	int		start_x = (int)(data->player.x * PIXELS_PER_CELL);
	int		start_y = (int)(data->player.y * PIXELS_PER_CELL);
	int		end_x = start_x + (int)dx;
	int		end_y = start_y + (int)dy;

	draw_line_bresenham(data, start_x, start_y, end_x, end_y, convert_color(255, 255, 0));
}

