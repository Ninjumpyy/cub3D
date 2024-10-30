/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:23:45 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 14:27:01 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_move(int keycode, t_data *data)
{
	if (keycode == 119)
		data->key.w = 1;
	if (keycode == 115)
		data->key.s = 1;
	if (keycode == 97)
		data->key.a = 1;
	if (keycode == 100)
		data->key.d = 1;
	if (keycode == 65363)
		data->key.right = 1;
	if (keycode == 65361)
		data->key.left = 1;
	if (keycode == 32)
		data->key.space = 1;
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
	if (data->state == GAME_START)
	{
		if (keycode == 65293)
			data->state = GAME_RUNNING;
	}
	else
		key_move(keycode, data);
	return (0);
}

int	key_released(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == 119)
		data->key.w = 0;
	if (keycode == 115)
		data->key.s = 0;
	if (keycode == 97)
		data->key.a = 0;
	if (keycode == 100)
		data->key.d = 0;
	if (keycode == 65363)
		data->key.right = 0;
	if (keycode == 65361)
		data->key.left = 0;
	if (keycode == 32)
		data->key.space = 0;
	return (0);
}
