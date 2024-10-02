/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:36:34 by thomas            #+#    #+#             */
/*   Updated: 2024/10/02 15:28:00 by thomas           ###   ########.fr       */
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
	if (keycode == 97 || keycode == 100 || keycode == 115 || keycode == 119)
		move_player(keycode, data);
	else
		printf("%i\n", keycode);
	return (0);
}

int	wall_collision(int keycode, t_data *data)
{
	float	limit;
	
	limit = ((SIZE_PIXEL_PLAYER / 2) * CELLS_PER_PIXEL);
	//printf("player_x : %f, player_y : %f\n", data->player.x, data->player.y);
	if (keycode == 119)
	{
		if (data->env.map[(int)(data->player.y - (SPEED * CELLS_PER_PIXEL) - limit)][(int)(data->player.x - limit)] == '1' || 
			data->env.map[(int)(data->player.y - (SPEED * CELLS_PER_PIXEL) - limit)][(int)(data->player.x + limit)] == '1')
			return (1);
	}
	if (keycode == 115)
	{
		if (data->env.map[(int)(data->player.y + (SPEED * CELLS_PER_PIXEL) + limit)][(int)(data->player.x - limit)] == '1' ||
			data->env.map[(int)(data->player.y + (SPEED * CELLS_PER_PIXEL) + limit)][(int)(data->player.x + limit)] == '1')
		return (1);
	}
	if (keycode == 97)
	{
		if (data->env.map[(int)(data->player.y - limit)][(int)(data->player.x - (SPEED * CELLS_PER_PIXEL) - limit)] == '1' ||
			data->env.map[(int)(data->player.y + limit)][(int)(data->player.x - (SPEED * CELLS_PER_PIXEL) - limit)] == '1')
		return (1);
	}
	if (keycode == 100)
	{
		if (data->env.map[(int)(data->player.y - limit)][(int)(data->player.x + (SPEED * CELLS_PER_PIXEL) + limit)] == '1' ||
			data->env.map[(int)(data->player.y + limit)][(int)(data->player.x + (SPEED * CELLS_PER_PIXEL) + limit)] == '1')
		return (1);
	}
	return (0);
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == 119 && !wall_collision(keycode, data)) // W
		data->player.y -= (SPEED * CELLS_PER_PIXEL);
	if (keycode == 115 && !wall_collision(keycode, data)) // S
		data->player.y += (SPEED * CELLS_PER_PIXEL);
	if (keycode == 97 && !wall_collision(keycode, data)) // A
		data->player.x -= (SPEED * CELLS_PER_PIXEL);
	if (keycode == 100 && !wall_collision(keycode, data)) // D
		data->player.x += (SPEED * CELLS_PER_PIXEL);
	redraw_minimap(data);
}

void	redraw_minimap(t_data *data)
{
	draw_minimap(data);
	draw_grid(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, 0, 0);
}

int	close_event(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_cub3d(data);
	exit(EXIT_SUCCESS);
}