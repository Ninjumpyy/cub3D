/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:05:05 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/17 15:54:15 by tle-moel         ###   ########.fr       */
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
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.minimap.img, 0, 0);
	//ft_printf("After render minimap\n");
	//draw_pixel(&(data.minimap), data.map_data->player_x, data.map_data->player_y, convert_color(255, 255, 0));
	mlx_loop(data.mlx);
	return (0);
}

void	cub_init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEI, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEI);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, \
		&data->minimap.line_size, &data->minimap.endian);
}

void	render_minimap(t_data *data, int player_x, int player_y)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	start_x = player_x - (VIEWPORT_CELLS / 2);
	start_y = player_y - (VIEWPORT_CELLS / 2);
	if (start_x + VIEWPORT_CELLS > data->map_data->width)
		start_x = data->map_data->width - VIEWPORT_CELLS;
	if (start_y + VIEWPORT_CELLS > data->map_data->height)
		start_y = data->map_data->height - VIEWPORT_CELLS;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	y = 0;
	//ft_printf("render minimap...\n");
	//ft_printf("start_x : %i, start_y : %i\n", start_x, start_y);
	while (y < VIEWPORT_CELLS)
	{
		x = 0;
		while (x < VIEWPORT_CELLS)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			draw_cell(data, map_x, map_y);
			x++;
		}
		y++;
	}
}

void	draw_cell(t_data *data, int map_x, int map_y)
{
	int	i;
	int	j;
	int color;

	//ft_printf("\nDraw_cell...\n");
	//ft_printf("map_x : %i, map_y : %i\n", map_x, map_y);
	//ft_printf("[map_y][map_x] : %c\n", data->map_data->map[map_y][map_x]);
	if (map_x > data->map_data->width - 1 || map_y > data->map_data->height - 1)
		color = convert_color(169, 169, 169);
	else if (data->map_data->map[map_y][map_x] == ' ' || data->map_data->map[map_y][map_x] == '\0' || data->map_data->map[map_y][map_x] == '\n')
		color = convert_color(169, 169, 169);
	else if (data->map_data->map[map_y][map_x] == '1')
		color = convert_color(250, 250, 250);
	else
		color = convert_color(0, 0, 0);
	j = 0;
	while (j < CELL_SIZE)
	{
		i = 0;
		while (i < CELL_SIZE)
		{
			draw_pixel(&(data)->minimap, (map_x * CELL_SIZE) + i, (map_y * CELL_SIZE) + j, color);
			i++;
		}
		j++;
	}
}
void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
