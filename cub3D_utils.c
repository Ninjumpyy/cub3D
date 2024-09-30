/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:04:39 by thomas            #+#    #+#             */
/*   Updated: 2024/09/30 18:18:19 by thomas           ###   ########.fr       */
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

int	convert_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	find_color(int x, int y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = x / CELL_SIZE;
	map_y = y / CELL_SIZE;
	if (data->env.map[map_y][map_x] == '1')
		return(convert_color(250, 250, 250));
	else if (data->env.map[map_y][map_x] == ' ' || data->env.map[map_y][map_x] == '\0' || data->env.map[map_y][map_x] == '\n')
		return(convert_color(169, 169, 169));
	else
		return(convert_color(0, 0, 0));
}
