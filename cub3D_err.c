/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:36:31 by thomas            #+#    #+#             */
/*   Updated: 2024/09/16 13:13:01 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	err_parsing(char **line, int fd, t_map_spec *map_data)
{
	free_get_next_line(fd, line);
	free_map_data(map_data);
	free(map_data);
	if (*line)
		free(*line);
	close(fd);
	if (write(2, "Error: .cub file\n", 18) == -1)
		exit(1);
	exit(1);
}

void	err_map(t_lst *raw_map, t_map_spec *map_data)
{
	free_map_data(map_data);
	free(map_data);
	free_lst(raw_map);
	if (write(2, "Error: .cub file\n", 18) == -1)
		exit(1);
	exit(1);
}

void	err_malloc(int fd)
{
	close(fd);
	if (write(2, "Error: .cub file\n", 18) == -1)
		exit(1);
	exit(1);
}
