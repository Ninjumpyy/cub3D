/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:05:05 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/17 17:06:51 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	parsing(argv[1], &data);
	//ft_printf("start x : %i\nstart y : %i\nwidth : %i\nheight : %i\n", data.map_data->player_x, data.map_data->player_y, data.map_data->width, data.map_data->height);

	cub_init(&data);
	render_minimap(&data, data.map_data->player_x, data.map_data->player_y);
	draw_player(&data, data.map_data->player_x, data.map_data->player_y);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L << 0, cub_key, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, cub_close, &data);
	mlx_loop(data.mlx);
	return (0);
}

int	cub_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
		cub_escape(data);
	return (0);
}

void	cub_escape(t_data *data)
{
	free_map_data(data->map_data);
	free(data->map_data);
	mlx_destroy_image(data->mlx, data->minimap.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int	cub_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->map_data)
	{
		free_map_data(data->map_data);
		free(data->map_data);
	}
	if (data->minimap.img)
		mlx_destroy_image(data->mlx, data->minimap.img);
	/*if (data->cub.img)
		mlx_destroy_image(data->mlx, data->cub.img);*/
	if (data->mlx_win && data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	draw_player(t_data *data, int player_x, int player_y)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = player_x * CELL_SIZE + (CELL_SIZE / 4);
	y = player_y * CELL_SIZE + (CELL_SIZE / 4);
	j = 0;
	while (j < PLAYER_SIZE)
	{
		i = 0;
		while (i < PLAYER_SIZE)
		{
			draw_pixel(&(data)->minimap, x + i, y + j, convert_color(255, 255, 0));
			i++;
		}
		j++;
	}
}

void	cub_init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEI, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEI);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, \
		&data->minimap.line_size, &data->minimap.endian);
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
