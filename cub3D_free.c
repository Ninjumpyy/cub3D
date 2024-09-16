/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:35:07 by thomas            #+#    #+#             */
/*   Updated: 2024/09/16 13:04:29 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_lst(t_lst *lst)
{
	t_lst	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = lst->next;
		free(ptr->line);
		free(ptr);
	}
}

void	free_map(t_map_spec *map_data)
{
	int	i;

	i = 0;
	while (map_data->map[i])
	{
		free(map_data->map[i]);
		i++;
	}
	free(map_data->map);
}

void	free_get_next_line(int fd, char **line)
{
	while (*line != NULL)
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

void	free_map_data(t_map_spec *map_data)
{
	if (map_data->no)
	{
		free(map_data->no);
		map_data->no = NULL;
	}
	if (map_data->so)
	{
		free(map_data->so);
		map_data->so = NULL;
	}
	if (map_data->we)
	{
		free(map_data->we);
		map_data->we = NULL;
	}
	if (map_data->ea)
	{
		free(map_data->ea);
		map_data->ea = NULL;
	}
	if (map_data->map)
	{
		free_map(map_data);
		map_data->map = NULL;
	}
}
