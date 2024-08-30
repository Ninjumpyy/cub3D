/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:05:05 by tle-moel          #+#    #+#             */
/*   Updated: 2024/08/30 11:08:01 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	if (parsing(argv[1], &data) == 1)
		return (1);
	ft_printf("cub3D in process...\n");
	return (0);
}