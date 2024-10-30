/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:39 by thomas            #+#    #+#             */
/*   Updated: 2024/10/30 10:47:33 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_get_next_line(int fd, char **line)
{
	if (*line)
	{
		while (*line != NULL)
		{
			free(*line);
			*line = get_next_line(fd);
		}
	}
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->env.map[i])
	{
		free(data->env.map[i]);
		i++;
	}
	free(data->env.map);
}

void	free_lst(t_lst **map_lst)
{
	t_lst	*ptr;

	if (map_lst && *map_lst)
	{
		while (*map_lst)
		{
			ptr = *map_lst;
			*map_lst = (*map_lst)->next;
			free(ptr->line);
			free(ptr);
		}
		*map_lst = NULL;
	}
}

void	free_doors(t_data *data)
{
	t_door	*ptr;

	while (data->doors)
	{
		ptr = data->doors->next;
		free(data->doors);
		data->doors = ptr;
	}
	if (data->text_data.door.img)
		mlx_destroy_image(data->mlx, data->text_data.door.img);
}

void	free_cub3d(t_data *data)
{
	free_env(data);
	free_doors(data);
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->minimap.img);
	mlx_destroy_image(data->mlx, data->cub.img);
	mlx_destroy_image(data->mlx, data->text_data.north.img);
	mlx_destroy_image(data->mlx, data->text_data.south.img);
	mlx_destroy_image(data->mlx, data->text_data.east.img);
	mlx_destroy_image(data->mlx, data->text_data.west.img);
	mlx_destroy_image(data->mlx, data->start.img);
	free_animation(&data->player, data);
	mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
