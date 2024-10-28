/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:04:39 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 14:17:00 by rpandipe         ###   ########.fr       */
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
	struct timeval	tv;

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
