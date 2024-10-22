/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:04:39 by thomas            #+#    #+#             */
/*   Updated: 2024/10/22 13:14:49 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_arg(int argc, char **argv)
{
	char	*term;

	if (argc != 2)
	{
		ft_error("Error\nWrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	term = ft_strrchr(argv[1], '.');
	if (!term || ft_strcmp(term, ".cub") != 0)
	{
		ft_error("Error\n.cub file required\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_error(const char *str)
{
	while (*str)
	{
		if (write(2, str, 1) == -1)
		{
			perror("Error\nFailed to write error message");
			exit(EXIT_FAILURE);
		}
		str++;
	}
}
 
double	get_time(void)
{
	struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
	{
		if (write(2, "Error\ngettimeofday() error\n", 27))
			perror("Error\nFailed to write error message");
	}
    return (tv.tv_sec + (double)tv.tv_usec / 1000000);
}

double	update_time(t_data *data)
{
	double	current_time;
	double	delta_time;
	
	current_time = get_time();
	delta_time = current_time - data->last_frame_time;
	data->last_frame_time = current_time;
	return (delta_time);
}

void	init_data(t_data *data)
{
	data->last_frame_time = get_time();
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, &data->minimap.line_size, &data->minimap.endian);
	data->cub.img = mlx_new_image(data->mlx, CUB_WIDTH, CUB_HEIGHT);
	data->cub.addr = mlx_get_data_addr(data->cub.img, &data->cub.bits_per_pixel, &data->cub.line_size, &data->cub.endian);
	data->text_data.north.img = mlx_xpm_file_to_image(data->mlx, data->env.no_texture, &data->text_data.north.width, &data->text_data.north.height);
	data->text_data.north.addr = mlx_get_data_addr(data->text_data.north.img, &data->text_data.north.bits_per_pixel, &data->text_data.north.line_size, &data->text_data.north.endian);
	data->text_data.south.img = mlx_xpm_file_to_image(data->mlx, data->env.so_texture, &data->text_data.south.width, &data->text_data.south.height);
	data->text_data.south.addr = mlx_get_data_addr(data->text_data.south.img, &data->text_data.south.bits_per_pixel, &data->text_data.south.line_size, &data->text_data.south.endian);
	data->text_data.east.img = mlx_xpm_file_to_image(data->mlx, data->env.ea_texture, &data->text_data.east.width, &data->text_data.east.height);
	data->text_data.east.addr = mlx_get_data_addr(data->text_data.east.img, &data->text_data.east.bits_per_pixel, &data->text_data.east.line_size, &data->text_data.east.endian);
	data->text_data.west.img = mlx_xpm_file_to_image(data->mlx, data->env.we_texture, &data->text_data.west.width, &data->text_data.west.height);
	data->text_data.west.addr = mlx_get_data_addr(data->text_data.west.img, &data->text_data.west.bits_per_pixel, &data->text_data.west.line_size, &data->text_data.west.endian);
	data->player.mouse_x = CUB_WIDTH / 2;
	data->player.mouse_y = CUB_HEIGHT / 2;
	data->player.sprite.img.width = 512;
	data->player.sprite.img.height = 512;
	data->player.sprite.img.img = mlx_xpm_file_to_image(data->mlx, "./textures/player.xpm", &(data->player.sprite.img.width), &(data->player.sprite.img.height));
	data->player.sprite.img.addr = mlx_get_data_addr(data->player.sprite.img.img, &data->player.sprite.img.bits_per_pixel, &data->player.sprite.img.line_size, &data->player.sprite.img.endian);
}
