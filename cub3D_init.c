/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:12:58 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/30 10:57:40 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_image(t_data *data, char *path, t_texture *tx)
{
	tx->img = mlx_xpm_file_to_image(data->mlx, path, &tx->width, &tx->height);
	if (!tx->img)
		err_cub3d("Error\nMemory allocation failed\n", data);
	tx->addr = mlx_get_data_addr(tx->img, &tx->bits_per_pixel, \
									&tx->line_size, &tx->endian);
	if (!tx->addr)
		err_cub3d("Error\nMemory allocation failed\n", data);
}

void	init_door(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->env.map[y][x] == '2')
			{
				if (data->text_data.door.img)
					add_door(data, x, y);
				else
					data->env.map[y][x] = '1';
			}
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->state = GAME_START;
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, \
											&data->minimap.bits_per_pixel, \
											&data->minimap.line_size, \
											&data->minimap.endian);
	data->cub.img = mlx_new_image(data->mlx, CUB_WIDTH, CUB_HEIGHT);
	data->cub.addr = mlx_get_data_addr(data->cub.img, \
			&data->cub.bits_per_pixel, &data->cub.line_size, &data->cub.endian);
	data->start.img = mlx_xpm_file_to_image(data->mlx, \
			"./textures/start.xpm", &data->start.width, &data->start.height);
	init_image(data, data->env.no_texture, &data->text_data.north);
	init_image(data, data->env.so_texture, &data->text_data.south);
	init_image(data, data->env.ea_texture, &data->text_data.east);
	init_image(data, data->env.we_texture, &data->text_data.west);
	if (data->env.door_texture)
		init_image(data, data->env.door_texture, &data->text_data.door);
	data->player.mouse_x = CUB_WIDTH / 2;
	data->player.mouse_y = CUB_HEIGHT / 2;
	load_animation(data);
	data->last_frame_time = get_time();
}
