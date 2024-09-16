/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:05:05 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/16 17:31:54 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	parsing(argv[1], &data);
	//ft_printf("start x : %i\nstart y : %i\nwidth : %i\nheight : %i\n", data.map_data->start_x, data.map_data->start_y, data.map_data->width, data.map_data->height);

	cub_init(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 0, 0);
	draw_player(&data, data.map_data->start_x, data.map_data->start_y, convert_color(255, 255, 0));
	mlx_loop(data.mlx);
	return (0);
}

void	cub_init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEI, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEI);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, \
		&data->minimap.line_size, &data->minimap.endian);
}

void	draw_player(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->minimap.addr + ()
}
