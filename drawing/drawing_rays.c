/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/04 22:33:05 by thomas           ###   ########.fr       */
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
	float	cotan;

	ray.x = 0;
	ray.y = 0;
	xo = 0;
	yo = 0;
	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray.angle = data->player.angle;
	r = 0;
	cotan = 1 / tan(ray.angle);
	printf("px : %f, py : %f\n", px, py);
	while (r < 1)
	{
		// ---Check Horizontal Lines---
		dof = 0;
		if (ray.angle < PI) // Looking up
		{
			printf("less than pi\n");
			ray.y = ((int)data->player.y * PIXELS_PER_CELL) - 0.0001;
			ray.x = (ray.y - py) * -1 * cotan + px;
			yo = - PIXELS_PER_CELL;
			xo = yo * (-1 * cotan); 
		}
		else if (ray.angle > PI) // Looking down
		{
			printf("more than pi\n");
			ray.y = ((int)data->player.y * PIXELS_PER_CELL) + PIXELS_PER_CELL;
			ray.x = (ray.y - py) * -1 * cotan + px;
			yo = PIXELS_PER_CELL;
			xo = yo * (-1 * cotan);
		}
		if (ray.angle == 0 || ray.angle == PI) // Looking straight left or right
		{
			printf("pi or 0\n");
			ray.x = px;
			ray.y = py;
			dof = 16;
		}
		printf("ray.angle : %f\n", ray.angle);
		printf("xo : %f, yo : %f\n", xo, yo);
		while (dof < 16)
		{
			if (ray.x < 0)
			{
				dof = 16;
				ray.x = 0;
			}
			if (ray.y < 0)
			{
				dof = 16;
				ray.y = 0;
			}
			if (ray.x >= MINIMAP_WIDTH)
			{
				dof = 16;
				ray.x = MINIMAP_WIDTH - 1;
			}
			if (ray.y >= MINIMAP_HEIGHT)
			{
				dof = 16;
				ray.y = MINIMAP_HEIGHT - 1;
			}
			printf("dof : %i\n", dof);
			printf("ray.x : %f, ray.y : %f\n", ray.x, ray.y);
			if (ray.x >= 0 && ray.y >= 0 && ray.x < MINIMAP_WIDTH && ray.y < MINIMAP_HEIGHT && data->env.map[(int)(ray.y * CELLS_PER_PIXEL)][(int)(ray.x * CELLS_PER_PIXEL)] == '1')
			{
				printf("found wall!\n");
				dof = 16;
			}
			else
			{
				ray.x += xo;
				ray.y += yo;
				dof++;
			}
		}
		r++;
	}
	draw_line(data, (int)ray.x, (int)ray.y, convert_color(0, 128, 0));
}
