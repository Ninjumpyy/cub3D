/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:49:33 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 14:18:07 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_data *data, double delta_time)
{
	double	move_x;
	double	move_y;
	double	move_speed;
	double	magnitude;

	move_speed = MOVE_SPEED * delta_time;
	move_x = 0;
	move_y = 0;
	compute_directional_movement(data, &move_x, &move_y, move_speed);
	magnitude = sqrt(move_x * move_x + move_y * move_y);
	if (magnitude > move_speed)
	{
		move_x = (move_x / magnitude) * move_speed;
		move_y = (move_y / magnitude) * move_speed;
	}
	if (can_move_to(move_x, move_y, data))
	{
		data->player.x += move_x;
		data->player.y += move_y;
	}
}

void	compute_directional_movement(t_data *data, double *move_x, \
								double *move_y, double move_speed)
{
	if (data->key.w == 1)
	{
		*move_x += cos(data->player.angle) * move_speed;
		*move_y -= sin(data->player.angle) * move_speed;
	}
	if (data->key.s == 1)
	{
		*move_x -= cos(data->player.angle) * move_speed;
		*move_y += sin(data->player.angle) * move_speed;
	}
	if (data->key.a == 1)
	{
		*move_x += sin(data->player.angle) * move_speed;
		*move_y += cos(data->player.angle) * move_speed;
	}
	if (data->key.d == 1)
	{
		*move_x -= sin(data->player.angle) * move_speed;
		*move_y -= cos(data->player.angle) * move_speed;
	}
}

int	if_door_not_open(t_data *data, int x, int y)
{
	t_door	*door;

	if (data->env.map[y][x] == '2')
	{
		door = find_door(data, x, y);
		if (door->open_amount != 1.0)
			return (1);
		return (0);
	}
	return (0);
}

int	can_move_to(double move_x, double move_y, t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x + move_x;
	new_y = data->player.y + move_y;
	limit = (SIZE_PIXEL_PLAYER / 2 * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y - limit)][(int)(new_x - limit)] == '1' ||
		data->env.map[(int)(new_y - limit)][(int)(new_x + limit)] == '1' ||
		data->env.map[(int)(new_y + limit)][(int)(new_x - limit)] == '1' ||
		data->env.map[(int)(new_y + limit)][(int)(new_x + limit)] == '1' ||
		if_door_not_open(data, (int)(new_x - limit), (int)(new_y - limit)) ||
		if_door_not_open(data, (int)(new_x + limit), (int)(new_y - limit)) ||
		if_door_not_open(data, (int)(new_x - limit), (int)(new_y + limit)) ||
		if_door_not_open(data, (int)(new_x + limit), (int)(new_y + limit)))
		return (0);
	else
		return (1);
}
