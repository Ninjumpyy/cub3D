/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 16:15:07 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_rays(t_data *data)
{
	int		r;
	int		dof;
	float	px;
	float	py;
	float	xo;
	float	yo;
	t_ray	ray;
	float	atan;

	ray.x = 0;
	ray.y = 0;
	xo = 0;
	yo = 0;
	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray.angle = data->player.angle;
	r = 0;
	atan = -1 / tan(ray.angle);
	while (r < 1)
	{
		// ---Check Horizontal Lines---
		dof = 0;
		if (ray.angle < PI) // Looking up
		{
			ray.y = (((int)py>>5)<<5) - 0.0001;
			ray.x = (py - ray.y) * atan + px;
			yo = - PIXELS_PER_CELL;
			xo = yo * atan; 
		}
		if (ray.angle > PI) // Looking down
		{
			ray.y = (((int)py>>5)<<5) + PIXELS_PER_CELL;
			ray.x = (py - ray.y) * atan + px;
			yo = PIXELS_PER_CELL;
			xo = yo * atan;
		}
		if (ray.angle == 0 || ray.angle == PI) // Looking straight left or right
		{
			ray.x = px;
			ray.y = py;
			dof = 8;
		}
		while (dof < 8)
		{
			if (ray.x >= 0 && ray.y >= 0 && ray.x < MINIMAP_WIDTH && ray.y < MINIMAP_HEIGHT && data->env.map[(int)(ray.y * CELLS_PER_PIXEL)][(int)(ray.x * CELLS_PER_PIXEL)] == '1')
				dof = 8;
			else
			{
				ray.x += xo;
				ray.y += yo;
				dof++;
			}
		}
		r++;
	}
	draw_line_bresenham(data, (int)px, (int)py, (int)ray.x, (int)ray.y, convert_color(255, 0, 0)); //responsible for drawing the ray for the moment
}