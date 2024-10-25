/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:03:18 by thomas            #+#    #+#             */
/*   Updated: 2024/10/25 17:29:06 by rpandipe         ###   ########.fr       */
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
	draw_background(&data);
	draw_minimap(&data);
	draw_cub_scene(&data);
	draw_crosshair(&data);
	draw_player_sprite(&data, &data.player.sprite.img);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.cub.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 10, 7);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	mlx_hook(data.mlx_win, 6, 1L << 6, mouse_event, &data);
	mlx_hook(data.mlx_win, 4, 1L << 2, button_pressed, &data);
	//mlx_hook(data.mlx_win, 5, 1L << 3, button_released, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_released, &data);
	mlx_loop_hook(data.mlx, player_event, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, close_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
