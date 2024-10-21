/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:59:37 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/21 11:30:44 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

void	init_ray_data(t_data *data, t_ray *ray, int reinit, t_type type)
{
	ray->x = data->player.x * PIXELS_PER_CELL;
	ray->y = data->player.y * PIXELS_PER_CELL;
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
}

void	init_horizontal_ray(t_data *data, t_ray *ray, int px, int py)
{
	float	cotan;

	cotan = 1 / tan(ray->angle);
	if (ray->angle < PI) // Looking up
	{
		ray->y = ((int)data->player.y * PIXELS_PER_CELL) - 0.0001;
		ray->x = (ray->y - py) * -1 * cotan + px;
		ray->yo = - PIXELS_PER_CELL;
		ray->xo = ray->yo * (-1 * cotan);
		ray->texture = data->text_data.south;
		//printf("SOUTH: %p\n", data->texture.south.img);
	}
	else if (ray->angle > PI) // Looking down
	{
		ray->y = ((int)data->player.y * PIXELS_PER_CELL) + PIXELS_PER_CELL;
		ray->x = (ray->y - py) * -1 * cotan + px;
		ray->yo = PIXELS_PER_CELL;
		ray->xo = ray->yo * (-1 * cotan);
		ray->texture = data->text_data.north;
		//printf("NORTH: %p\n", data->texture.north.img);
	}
	if (ray->angle == 0 || ray->angle == PI) // Looking straight left or right
	{
		ray->x = data->player.x * PIXELS_PER_CELL;
		ray->y = data->player.y * PIXELS_PER_CELL;
		ray->dof = 16;
	}
}

void	init_vertical_ray(t_data *data, t_ray *ray, int px, int py)
{
	if (ray->angle < (PI / 2) || ray->angle > (3 * PI / 2)) // Looking right
		{
			ray->x = ((int)data->player.x * PIXELS_PER_CELL) + PIXELS_PER_CELL;
			ray->y = (ray->x - px) * -1 * tan(ray->angle) + py;
			ray->xo = PIXELS_PER_CELL;
			ray->yo = ray->xo * -1 * tan(ray->angle); 
			ray->texture = data->text_data.west;
			//printf("WEST: %p\n", data->texture.west.img);
		}
		else if (ray->angle > (PI / 2) && ray->angle < (3 * PI / 2)) // Looking left
		{
			ray->x = ((int)data->player.x * PIXELS_PER_CELL) - 0.0001;
			ray->y = (ray->x - px) * -1 * tan(ray->angle) + py;
			ray->xo = - PIXELS_PER_CELL;
			ray->yo = ray->xo * -1 * tan(ray->angle);
			ray->texture = data->text_data.east;
			//printf("EAST: %p\n", data->texture.east.img);
		}
		if (ray->angle == (PI / 2) || ray->angle == (3 * PI / 2)) // Looking up or down
		{
			ray->x = px;
			ray->y = py;
			ray->dof = 16;
		}
}

void	determine_hit_ray(t_data *data, t_ray *ray)
{
	while (ray->dof < 16)
	{
		if (ray->x < 0 || ray->x >= MINIMAP_WIDTH || ray->y < 0 || ray->y >= MINIMAP_HEIGHT || \
		data->env.map[(int)(ray->y * CELLS_PER_PIXEL)][(int)(ray->x * CELLS_PER_PIXEL)] == '1')
		{
			ray->dof = 16;
			if (ray->x < 0)
				ray->x = 0;
			if (ray->x >= MINIMAP_WIDTH)
				ray->x = MINIMAP_WIDTH - 1;
			if (ray->y < 0)
				ray->y = 0;
			if (ray->y >= MINIMAP_HEIGHT)
				ray->y = MINIMAP_HEIGHT - 1;
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

	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray->dist = sqrt((ray->x - px) * (ray->x - px) + (ray->y - py) * (ray->y - py));
}
