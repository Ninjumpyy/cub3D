/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/05 12:05:51 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	calculate_distance(t_data *data, t_ray ray)
{
	float	px;
	float	py;

	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	return (sqrt((ray.x - px) * (ray.x - px) + (ray.y - py) * (ray.y - py)));
}

void	draw_rays(t_data *data)
{
	int		r;
	int		dof;
	float	px;
	float	py;
	float	xo;
	float	yo;
	t_ray	ray_h;
	t_ray	ray_v;
	float	cotan;
	float	dist_h;
	float	dist_v;

	xo = 0;
	yo = 0;
	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray_h.x = px;
	ray_h.y = py;
	ray_h.angle = data->player.angle - (DR * 30);
	if (ray_h.angle < 0)
		ray_h.angle += (2 * PI);
	if (ray_h.angle > 2 * PI)
		ray_h.angle -= (2 * PI);
	ray_v.angle = ray_h.angle;
	r = 0;
	while (r < 60)
	{
		cotan = 1 / tan(ray_h.angle);
		printf("angle : %f  %f\n", ray_h.angle, ray_v.angle);
		// ---Check Horizontal Lines---
		
		dof = 0;
		dist_h = 1000000;
		if (ray_h.angle < PI) // Looking up
		{
			ray_h.y = ((int)data->player.y * PIXELS_PER_CELL) - 0.0001;
			ray_h.x = (ray_h.y - py) * -1 * cotan + px;
			yo = - PIXELS_PER_CELL;
			xo = yo * (-1 * cotan); 
		}
		else if (ray_h.angle > PI) // Looking down
		{
			ray_h.y = ((int)data->player.y * PIXELS_PER_CELL) + PIXELS_PER_CELL;
			ray_h.x = (ray_h.y - py) * -1 * cotan + px;
			yo = PIXELS_PER_CELL;
			xo = yo * (-1 * cotan);
		}
		if (ray_h.angle == 0 || ray_h.angle == PI) // Looking straight left or right
		{
			ray_h.x = px;
			ray_h.y = py;
			dof = 16;
		}
		while (dof < 16)
		{
			if (ray_h.x < 0)
			{
				dof = 16;
				ray_h.x = 0;
			}
			if (ray_h.y < 0)
			{
				dof = 16;
				ray_h.y = 0;
			}
			if (ray_h.x >= MINIMAP_WIDTH)
			{
				dof = 16;
				ray_h.x = MINIMAP_WIDTH - 1;
			}
			if (ray_h.y >= MINIMAP_HEIGHT)
			{
				dof = 16;
				ray_h.y = MINIMAP_HEIGHT - 1;
			}
			if (data->env.map[(int)(ray_h.y * CELLS_PER_PIXEL)][(int)(ray_h.x * CELLS_PER_PIXEL)] == '1')
				dof = 16;
			else
			{
				ray_h.x += xo;
				ray_h.y += yo;
				dof++;
			}
		}
		dist_h = calculate_distance(data, ray_h);

		// ---Check Vertical Lines---
		ray_v.x = px;
		ray_v.y = py;
		dof = 0;
		dist_v = 1000000;
		if (ray_v.angle < (PI / 2) || ray_v.angle > (3 * PI / 2)) // Looking right
		{
			ray_v.x = ((int)data->player.x * PIXELS_PER_CELL) + PIXELS_PER_CELL;
			ray_v.y = (ray_v.x - px) * -1 * tan(ray_v.angle) + py;
			xo = PIXELS_PER_CELL;
			yo = xo * -1 * tan(ray_v.angle); 
		}
		else if (ray_v.angle > (PI / 2) && ray_v.angle < (3 * PI / 2)) // Looking left
		{
			ray_v.x = ((int)data->player.x * PIXELS_PER_CELL) - 0.0001;
			ray_v.y = (ray_v.x - px) * -1 * tan(ray_v.angle) + py;
			xo = - PIXELS_PER_CELL;
			yo = xo * -1 * tan(ray_v.angle);
		}
		if (ray_v.angle == (PI / 2) || ray_v.angle == (3 * PI / 2)) // Looking up or down
		{
			ray_v.x = px;
			ray_v.y = py;
			dof = 16;
		}
		while (dof < 16)
		{
			if (ray_v.x < 0)
			{
				dof = 16;
				ray_v.x = 0;
			}
			if (ray_v.y < 0)
			{
				dof = 16;
				ray_v.y = 0;
			}
			if (ray_v.x >= MINIMAP_WIDTH)
			{
				dof = 16;
				ray_v.x = MINIMAP_WIDTH - 1;
			}
			if (ray_v.y >= MINIMAP_HEIGHT)
			{
				dof = 16;
				ray_v.y = MINIMAP_HEIGHT - 1;
			}
			if (data->env.map[(int)(ray_v.y * CELLS_PER_PIXEL)][(int)(ray_v.x * CELLS_PER_PIXEL)] == '1')
				dof = 16;
			else
			{
				ray_v.x += xo;
				ray_v.y += yo;
				dof++;
			}
		}
		dist_v = calculate_distance(data, ray_v);
		printf("distH : %f, distV : %f\n", dist_h, dist_v);
		if (dist_v < dist_h)
		{
			printf("ray_v.x : %f, ray_v.y : %f\n", ray_v.x, ray_v.y);
			draw_line(data, (int)ray_v.x, (int)ray_v.y, convert_color(0, 128, 0));
		}
		else
		{
			printf("ray_h.x : %f, ray_h.y : %f\n", ray_h.x, ray_h.y);
			draw_line(data, (int)ray_h.x, (int)ray_h.y, convert_color(0, 128, 0));
		}
		r++;
		ray_h.angle += DR;
		if (ray_h.angle < 0)
			ray_h.angle += (2 * PI);
		if (ray_h.angle > 2 * PI)
			ray_h.angle -= (2 * PI);
		ray_v.angle = ray_h.angle;
	}
}
