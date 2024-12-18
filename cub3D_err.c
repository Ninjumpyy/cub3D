/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:43:49 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 11:39:52 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	err_parsing(char **line, int fd, t_data *data, t_lst **map_lst)
{
	free_get_next_line(fd, line);
	free_env(data);
	free_lst(map_lst);
	close(fd);
	ft_error("Error\n.cub file parsing\n");
	exit(EXIT_FAILURE);
}

void	err_cub3d(char *error, t_data *data)
{
	ft_error(error);
	free_cub3d(data);
	exit(EXIT_FAILURE);
}
