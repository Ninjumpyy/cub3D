/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:04:39 by thomas            #+#    #+#             */
/*   Updated: 2024/10/10 15:14:22 by tle-moel         ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, &data->minimap.line_size, &data->minimap.endian);
	data->cub.img = mlx_new_image(data->mlx, CUB_WIDTH, CUB_HEIGHT);
	data->cub.addr = mlx_get_data_addr(data->cub.img, &data->cub.bits_per_pixel, &data->cub.line_size, &data->cub.endian);
	data->texture.north.img = mlx_xpm_file_to_image(data->mlx, data->env.no_texture, &data->texture.north.width, &data->texture.north.height);
	data->texture.north.addr = mlx_get_data_addr(data->texture.north.img, &data->texture.north.bits_per_pixel, &data->texture.north.line_size, &data->texture.north.endian);
	data->texture.south.img = mlx_xpm_file_to_image(data->mlx, data->env.no_texture, &data->texture.south.width, &data->texture.south.height);
	data->texture.south.addr = mlx_get_data_addr(data->texture.south.img, &data->texture.south.bits_per_pixel, &data->texture.south.line_size, &data->texture.south.endian);
	data->texture.east.img = mlx_xpm_file_to_image(data->mlx, data->env.no_texture, &data->texture.east.width, &data->texture.east.height);
	data->texture.east.addr = mlx_get_data_addr(data->texture.east.img, &data->texture.east.bits_per_pixel, &data->texture.east.line_size, &data->texture.east.endian);
	data->texture.west.img = mlx_xpm_file_to_image(data->mlx, data->env.no_texture, &data->texture.west.width, &data->texture.west.height);
	data->texture.west.addr = mlx_get_data_addr(data->texture.west.img, &data->texture.west.bits_per_pixel, &data->texture.west.line_size, &data->texture.west.endian);
}
