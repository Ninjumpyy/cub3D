/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:39 by thomas            #+#    #+#             */
/*   Updated: 2024/09/30 12:23:38 by thomas           ###   ########.fr       */
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

void	free_env(t_data *data)
{
	if (data->env.no_texture)
	{
		free(data->env.no_texture);
		data->env.no_texture = NULL;
	}
	if (data->env.so_texture)
	{
		free(data->env.so_texture);
		data->env.so_texture = NULL;
	}
	if (data->env.we_texture)
	{
		free(data->env.we_texture);
		data->env.we_texture = NULL;
	}
	if (data->env.ea_texture)
	{
		free(data->env.ea_texture);
		data->env.ea_texture = NULL;
	}
	if (data->env.map)
	{
		free_map(data);
		data->env.map = NULL;
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
