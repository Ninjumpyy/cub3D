/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:58:35 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/18 13:59:12 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	max_height;

	max_height = CUB_HEIGHT / 2;
	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < CUB_WIDTH)
		{
			draw_pixel(&(data)->cub, x, y, convert_color(data->env.ceiling.r, data->env.ceiling.g, data->env.ceiling.b));
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	y = CUB_HEIGHT / 2;
	while (y < CUB_HEIGHT)
	{
		x = 0;
		while (x < CUB_WIDTH)
		{
			draw_pixel(&(data)->cub, x, y, convert_color(data->env.floor.r, data->env.floor.g, data->env.floor.b));
			x++;
		}
		y++;
	}
}