/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:00:22 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/01 13:01:40 by tle-moel         ###   ########.fr       */
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

	map_x = x / CELLS_PER_PIXEL;
	map_y = y / CELLS_PER_PIXEL;
	if (data->env.map[map_y][map_x] == '1')
		return(convert_color(250, 250, 250));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(169, 169, 169));
	else
		return(convert_color(0, 0, 0));
}
void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, &data->minimap.line_size, &data->minimap.endian);
}
