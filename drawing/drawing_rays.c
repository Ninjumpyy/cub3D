/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:59:37 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/28 11:52:51 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_ray_data(t_data *data, t_ray *ray, int reinit, t_type type)
{
	ray->x = data->player.x;
	ray->y = data->player.y;
	if (reinit == 0)
	{
		ray->angle = data->player.angle - (DR * (FOV / 2));
		normalize_angle(ray);
		ray->type = type;
		ft_memset(&(ray->texture), 0, sizeof(t_texture));
	}
	ray->dist = 1000000;
	ray->xo = 0;
	ray->yo = 0;
	ray->dof = 0;
	ray->open_amount = -1.0;
}

void	init_horizontal_ray(t_data *data, t_ray *ray, float px, float py)
{
	float	cotan;

	cotan = 1 / tan(ray->angle);
	if (ray->angle < PI)
	{
		ray->y = (int)data->player.y - 0.0001;
		ray->x = (ray->y - py) * -1 * cotan + px;
		ray->yo = -1;
		ray->xo = ray->yo * (-1 * cotan);
		ray->texture = data->text_data.south;
	}
	else if (ray->angle > PI)
	{
		ray->y = (int)(data->player.y + 1);
		ray->x = (ray->y - py) * -1 * cotan + px;
		ray->yo = 1;
		ray->xo = ray->yo * (-1 * cotan);
		ray->texture = data->text_data.north;
	}
	if (ray->angle == 0 || ray->angle == PI)
	{
		ray->x = px;
		ray->y = py;
		ray->dof = DOF_MAX;
	}
}

void	init_vertical_ray(t_data *data, t_ray *ray, float px, float py)
{
	if (ray->angle < (PI / 2) || ray->angle > (3 * PI / 2))
	{
		ray->x = (int)(data->player.x + 1);
		ray->y = (ray->x - px) * -1 * tan(ray->angle) + py;
		ray->xo = 1;
		ray->yo = ray->xo * -1 * tan(ray->angle);
		ray->texture = data->text_data.west;
	}
	else if (ray->angle > (PI / 2) && ray->angle < (3 * PI / 2))
	{
		ray->x = (int)data->player.x - 0.0001;
		ray->y = (ray->x - px) * -1 * tan(ray->angle) + py;
		ray->xo = -1;
		ray->yo = ray->xo * -1 * tan(ray->angle);
		ray->texture = data->text_data.east;
	}
	if ((ray->angle == (PI / 2)) || (ray->angle == (3 * PI / 2)))
	{
		ray->x = px;
		ray->y = py;
		ray->dof = DOF_MAX;
	}
}

void	determine_hit_ray(t_data *data, t_ray *ray)
{
	while (ray->dof < DOF_MAX)
	{
		if (ray->x < 0 || ray->x >= data->map_width || ray->y < 0
			|| ray->y >= data->map_height
			|| data->env.map[(int)ray->y][(int)ray->x] == '1')
			hit_ray_logic(data, ray);
		else if (data->env.map[(int)ray->y][(int)ray->x] == '2'
			&& !is_open(data, ray))
		{
			hit_ray_logic(data, ray);
			ray->texture = data->text_data.door;
		}
		else
		{
			ray->x += ray->xo;
			ray->y += ray->yo;
			ray->dof += 1;
		}
	}
}

void	calculate_distance(t_data *data, t_ray *ray)
{
	float	px;
	float	py;

	px = data->player.x;
	py = data->player.y;
	ray->dist = sqrt((ray->x - px) * (ray->x - px)
			+ (ray->y - py) * (ray->y - py)) * SCALING;
}
