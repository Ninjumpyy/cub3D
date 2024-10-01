/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:00:22 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/01 14:26:24 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	convert_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	find_color(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / PIXELS_PER_CELL;
	map_y = y / PIXELS_PER_CELL;
	if (data->env.map[map_y][map_x] == '1')
		return(convert_color(250, 250, 250));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(169, 169, 169));
	else
		return(convert_color(0, 0, 0));
}
