/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:35:07 by thomas            #+#    #+#             */
/*   Updated: 2024/09/10 10:36:02 by thomas           ###   ########.fr       */
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

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	free_get_next_line(int fd, char **line)
{
	while (*line != NULL)
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

void	free_data(t_data *data)
{
	if (data->no)
	{
		free(data->no);
		data->no = NULL;
	}
	if (data->so)
	{
		free(data->so);
		data->so = NULL;
	}
	if (data->we)
	{
		free(data->we);
		data->we = NULL;
	}
	if (data->ea)
	{
		free(data->ea);
		data->ea = NULL;
	}
	if (data->map)
	{
		free_map(data);
		data->map = NULL;
	}
}
