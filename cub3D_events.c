/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:36:34 by thomas            #+#    #+#             */
/*   Updated: 2024/10/23 14:41:24 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_event(int x, int y, void *param)
{
	t_data	*data;
	int			delta_x;

	(void)y;
	data = (t_data *)param;
	delta_x = x - (CUB_WIDTH / 2);
	//printf("position = %d\n", prev_x);
	if (delta_x != 0)
	{
		//printf("in here\n");
		data->player.angle -= delta_x * 0.02 / M_SENSITIVITY;
		if (data->player.angle > (2 * PI))
			data->player.angle -= (2 * PI);
		if (data->player.angle < 0)
			data->player.angle += (2 * PI);
		//redraw_minimap(data);
		mlx_mouse_move(data->mlx, data->mlx_win, CUB_WIDTH / 2, CUB_HEIGHT / 2);
	}
	//data->player.mouse_x = x;
	//data->player.mouse_y = y;
	//printf("Mouse moved to: x = %d, y = %d\n", x, y);
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == XK_Escape)
	{
		free_cub3d(data);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 119) // W
		data->key.w = 1;
	if (keycode == 115) // S
		data->key.s = 1;
	if (keycode == 97) // A
		data->key.a = 1;
	if (keycode == 100) // D
		data->key.d = 1;
	if (keycode == 65363) // right
		data->key.right = 1;
	if (keycode == 65361) // left
		data->key.left = 1;
	return (0);
}

int	key_released(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 119) // W
		data->key.w = 0;
	if (keycode == 115) // S
		data->key.s = 0;
	if (keycode == 97) // A
		data->key.a = 0;
	if (keycode == 100) // D
		data->key.d = 0;
	if (keycode == 65363) // right
		data->key.right = 0;
	if (keycode == 65361) // left
		data->key.left = 0;
	return (0);
}

int	player_event(t_data *data)
{
	double	delta_time;
	
	delta_time = update_time(data);
	if (data->key.w == 1 || data->key.s == 1 || data->key.a == 1 || data->key.d == 1)
		move_player(data, delta_time);
	if (data->key.right == 1) //right
	{
		data->player.angle -= delta_time * ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += (2 * PI);
	}
	if (data->key.left == 1) //left
	{
		data->player.angle += delta_time * ROTATION_SPEED;
		if (data->player.angle > (2 * PI))
			data->player.angle -= (2 * PI);
	}
	redraw_minimap(data);
	return (0);
}

int	close_event(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_cub3d(data);
	exit(EXIT_SUCCESS);
}