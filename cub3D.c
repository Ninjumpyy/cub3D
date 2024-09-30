/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:03:18 by thomas            #+#    #+#             */
/*   Updated: 2024/09/19 16:42:00 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	check_arg(argc, argv);
	ft_memset(&data, 0, sizeof(t_data));
	parsing_file(argv[1], &data);
	/*printf("map_width : %i, map_height : %i\n", data.map_width, data.map_height);
	printf("PLAYER :\n");
	printf("is_found : %i, x = %f, y = %f\n", data.player.is_found, data.player.x, data.player.y);
	printf("MAP :\n");*/
	int i = 0;
	while (i < data.map_height)
	{
		printf("%s", data.env.map[i]);
		i++;
	}
	return (0);
}
