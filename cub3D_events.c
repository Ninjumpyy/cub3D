/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:36:34 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 14:24:05 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_event(int x, int y, void *param)
{
	t_data	*data;
	int		delta_x;

	(void)y;
	data = (t_data *)param;
	delta_x = x - (CUB_WIDTH / 2);
	if (delta_x != 0)
	{
		data->player.angle += delta_x * 0.02 / M_SENSITIVITY;
		if (data->player.angle > (2 * PI))
			data->player.angle -= (2 * PI);
		if (data->player.angle < 0)
			data->player.angle += (2 * PI);
		mlx_mouse_move(data->mlx, data->mlx_win, CUB_WIDTH / 2, CUB_HEIGHT / 2);
	}
	return (0);
}

int	button_pressed(int button, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
	data = (t_data *)param;
	if (button == 1)
	{
		data->key.mouse_left = 1;
		data->animation_time = get_time();
	}
	return (0);
}

int	player_event(t_data *data)
{
	double	delta_time;

	delta_time = update_time(data);
	if (data->key.w == 1 || data->key.s == 1 || \
		data->key.a == 1 || data->key.d == 1)
		move_player(data, delta_time);
	if (data->key.right == 1)
	{
		data->player.angle += delta_time * ROTATION_SPEED;
		if (data->player.angle > (2 * PI))
			data->player.angle -= (2 * PI);
	}
	if (data->key.left == 1)
	{
		data->player.angle -= delta_time * ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += (2 * PI);
	}
	if (data->key.space == 1)
		action_door(data);
	update_doors(data, delta_time);
	if (data->key.mouse_left == 1)
		play_animation(data, &data->player.current_sprite);
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
