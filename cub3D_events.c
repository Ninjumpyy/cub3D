/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:36:34 by thomas            #+#    #+#             */
/*   Updated: 2024/10/08 16:53:01 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_event(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
	{
		free_cub3d(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
		move_player(keycode, data);
	else if (keycode == 65363 || keycode == 65361)
		rotate_player(keycode, data);
	else
		printf("%i\n", keycode);
	return (0);
}

void	rotate_player(int keycode, t_data *data)
{
	if (keycode == 65363) //right
	{
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > (2 * PI))
			data->player.angle -= (2 * PI);
	}
	if (keycode == 65361) //left
	{
		data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += (2 * PI);
	}
	redraw_minimap(data);
}

void	redraw_minimap(t_data *data)
{
	draw_ceiling(data);
	draw_floor(data);
	draw_minimap(data);
	draw_player(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->cub.img, 512, 0);
}

int	close_event(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_cub3d(data);
	exit(EXIT_SUCCESS);
}