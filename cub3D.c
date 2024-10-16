/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:03:18 by thomas            #+#    #+#             */
/*   Updated: 2024/10/16 12:57:08 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
void	print_debug(t_data data)
{
	printf("map_width : %i, map_height : %i\n", data.map_width, data.map_height);
	printf("PLAYER :\n");
	printf("is_found : %i, x = %f, y = %f\n", data.player.is_found, data.player.x, data.player.y);
	printf("MAP :\n");
	int i = 0;
	while (i < data.map_height)
	{
		printf("%s", data.env.map[i]);
		i++;
	}
}*/

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	ft_memset(&data, 0, sizeof(t_data));
	parsing_file(argv[1], &data);
	//print_debug(data);
	init_data(&data);
	printf("loaded player\n");
	draw_ceiling(&data);
	draw_floor(&data);
	draw_minimap(&data);
	cast_rays(&data);
	draw_player(&data);
	draw_crosshair(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 0, 0);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.cub.img, 512, 0);
	mlx_mouse_hide(data.mlx, data.mlx_win);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_event, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, mouse_event, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, close_event, &data);
	mlx_loop(data.mlx);
	return (0);
}
