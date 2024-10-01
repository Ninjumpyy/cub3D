/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:36:34 by thomas            #+#    #+#             */
/*   Updated: 2024/10/01 15:06:41 by tle-moel         ###   ########.fr       */
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
	if (keycode >= 65361 && keycode <= 65364)
		move_player(keycode, data);
	return (0);
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == 65362)
		data->player.y -= (SPEED * CELLS_PER_PIXEL); //up
	if (keycode == 65364)
		data->player.y += (SPEED * CELLS_PER_PIXEL); //down
	if (keycode == 65361)
		data->player.x -= (SPEED * CELLS_PER_PIXEL); //left
	if (keycode == 65363)
		data->player.x += (SPEED * CELLS_PER_PIXEL); //right
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