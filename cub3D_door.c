/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:45:25 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/28 10:40:20 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_open(t_data *data, t_ray *ray)
{
	t_door	*door;

	door = find_door(data, (int)ray->x, (int)ray->y);
	if (ray->type == HORIZONTAL)
	{
		if ((ray->x - (int)ray->x) > (1.0 - door->open_amount))
			return (1);
		ray->open_amount = door->open_amount;
		return (0);
	}
	else
	{
		if ((ray->y - (int)ray->y) > (1.0 - door->open_amount))
			return (1);
		ray->open_amount = door->open_amount;
		return (0);
	}
}

t_door	*find_door(t_data *data, int x, int y)
{
	t_door	*door;

	door = data->doors;
	while (door && (door->x != x || door->y != y))
	{
		door = door->next;
	}
	return (door);
}

void	action_door(t_data *data)
{
	int		px;
	int		py;
	t_door	*door;

	door = NULL;
	px = (int)data->player.x;
	py = (int)data->player.y;
	if (data->env.map[py - 1][px] == '2')
		door = find_door(data, px, py - 1);
	else if (data->env.map[py + 1][px] == '2')
		door = find_door(data, px, py + 1);
	else if (data->env.map[py][px - 1] == '2')
		door = find_door(data, px - 1, py);
	else if (data->env.map[py][px + 1] == '2')
		door = find_door(data, px + 1, py);
	if (door && door->open_amount == 0.0)
		door->opening = 1;
	else if (door && door->open_amount == 1.0)
		door->closing = 1;
}

void	update_doors(t_data *data, double delta_time)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (door->opening && door->open_amount < 1.0)
		{
			door->open_amount += delta_time * DOOR_OPEN_SPEED;
			if (door->open_amount > 1.0)
			{
				door->open_amount = 1.0;
				door->opening = 0;
			}
		}
		else if (door->closing && door->open_amount > 0.0)
		{
			door->open_amount -= delta_time * DOOR_OPEN_SPEED;
			if (door->open_amount < 0.0)
			{
				door->open_amount = 0.0;
				door->closing = 0;
			}
		}
		door = door->next;
	}
}

void	add_door(t_data *data, int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	door->x = x;
	door->y = y;
	door->open_amount = 0.0f;
	door->opening = 0;
	door->next = data->doors;
	data->doors = door;
}

void	init_door(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->env.map[y][x] == '2')
				add_door(data, x, y);
			x++;
		}
		y++;
	}
}
