/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:03:18 by thomas            #+#    #+#             */
/*   Updated: 2024/10/16 15:52:11 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	ft_memset(&data, 0, sizeof(t_data));
	parsing_file(argv[1], &data);
	init_data(&data);
	
	
	draw_ceiling(&data);
	draw_floor(&data);
	draw_minimap(&data);
	draw_player(&data);
	cast_rays(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.cub.img, 512, 0);

	
	mlx_hook(data.mlx_win, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_released, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, close_event, &data);
	mlx_loop_hook(data.mlx, player_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
