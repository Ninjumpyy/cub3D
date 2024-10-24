/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:43:49 by thomas            #+#    #+#             */
/*   Updated: 2024/09/30 16:34:00 by thomas           ###   ########.fr       */
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
