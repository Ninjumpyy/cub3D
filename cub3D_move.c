/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:49:33 by thomas            #+#    #+#             */
/*   Updated: 2024/10/03 10:28:28 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(int keycode, t_data *data)
{
	if (keycode == 119) // W
		move_forward(data);
	if (keycode == 115) // S
		move_backward(data);
	if (keycode == 97) // A
		move_left(data);
	if (keycode == 100) // D
		move_right(data);
}

void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x + cos(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	new_y = data->player.y - sin(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y - limit)][(int)(new_x - limit)] != '1' &&
		data->env.map[(int)(new_y - limit)][(int)(new_x + limit)] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
		redraw_minimap(data);
	}
}

void	move_backward(t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x - cos(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	new_y = data->player.y + sin(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y + limit)][(int)(new_x - limit)] != '1' &&
		data->env.map[(int)(new_y + limit)][(int)(new_x + limit)] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
		redraw_minimap(data);
	}
}

void	move_left(t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x - sin(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	new_y = data->player.y - cos(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y + limit)][(int)(new_x - limit)] != '1' &&
		data->env.map[(int)(new_y - limit)][(int)(new_x - limit)] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
		redraw_minimap(data);
	}
}

void	move_right(t_data *data)
{
	float	new_x;
	float	new_y;
	float	limit;

	new_x = data->player.x + sin(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	new_y = data->player.y + cos(data->player.angle) * (MOVE_SPEED * CELLS_PER_PIXEL);
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	if (data->env.map[(int)(new_y + limit)][(int)(new_x + limit)] != '1' &&
		data->env.map[(int)(new_y - limit)][(int)(new_x + limit)] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
		redraw_minimap(data);
	}
}

/*
int	wall_collision(int keycode, t_data *data)
{
	float	limit;
	
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	//printf("player_x : %f, player_y : %f\n", data->player.x, data->player.y);
	if (keycode == 119)
	{
		if (data->env.map[(int)(data->player.y - (MOVE_SPEED * CELLS_PER_PIXEL) - limit)][(int)(data->player.x - limit)] == '1' || 
			data->env.map[(int)(data->player.y - (MOVE_SPEED * CELLS_PER_PIXEL) - limit)][(int)(data->player.x + limit)] == '1')
			return (1);
	}
	if (keycode == 115)
	{
		if (data->env.map[(int)(data->player.y + (MOVE_SPEED * CELLS_PER_PIXEL) + limit)][(int)(data->player.x - limit)] == '1' ||
			data->env.map[(int)(data->player.y + (MOVE_SPEED * CELLS_PER_PIXEL) + limit)][(int)(data->player.x + limit)] == '1')
		return (1);
	}
	if (keycode == 97)
	{
		if (data->env.map[(int)(data->player.y - limit)][(int)(data->player.x - (MOVE_SPEED * CELLS_PER_PIXEL) - limit)] == '1' ||
			data->env.map[(int)(data->player.y + limit)][(int)(data->player.x - (MOVE_SPEED * CELLS_PER_PIXEL) - limit)] == '1')
		return (1);
	}
	if (keycode == 100)
	{
		if (data->env.map[(int)(data->player.y - limit)][(int)(data->player.x + (MOVE_SPEED * CELLS_PER_PIXEL) + limit)] == '1' ||
			data->env.map[(int)(data->player.y + limit)][(int)(data->player.x + (MOVE_SPEED * CELLS_PER_PIXEL) + limit)] == '1')
		return (1);
	}
	return (0);
}*/