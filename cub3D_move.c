/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:49:33 by thomas            #+#    #+#             */
/*   Updated: 2024/10/16 15:46:20 by tle-moel         ###   ########.fr       */
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

void	compute_directional_movement(t_data *data, double *move_x, double *move_y, double move_speed)
{
	if (data->key.w == 1) // W
	{
		*move_x += cos(data->player.angle) * move_speed;
		*move_y -= sin(data->player.angle) * move_speed;
	}
	if (data->key.s == 1) // S
	{
		*move_x -= cos(data->player.angle) * move_speed;
		*move_y += sin(data->player.angle) * move_speed;
	}
	if (data->key.a == 1) // A
	{
		*move_x += sin(data->player.angle) * move_speed;
		*move_y += cos(data->player.angle) * move_speed;
	}
	if (data->key.d == 1) // D
	{
		*move_x -= sin(data->player.angle) * move_speed;
		*move_y -= cos(data->player.angle) * move_speed;
	}
}

int	can_move_to(double move_x, double move_y, t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x + move_x;
	new_y = data->player.y + move_y;
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y - limit)][(int)(new_x - limit)] != '1' &&
		data->env.map[(int)(new_y - limit)][(int)(new_x + limit)] != '1' &&
		data->env.map[(int)(new_y + limit)][(int)(new_x - limit)] != '1' &&
		data->env.map[(int)(new_y + limit)][(int)(new_x + limit)] != '1')
		return (1);
	else
		return (0);
}
