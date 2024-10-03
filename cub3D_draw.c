/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:50:07 by thomas            #+#    #+#             */
/*   Updated: 2024/10/03 19:50:12 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_size + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			draw_pixel(&(data)->minimap, x, y, find_color(x, y, data));
			x++;
		}
		y++;
	}
}

void	draw_grid(t_data *data)
{
	int	x;
	int	y;

	y = PIXELS_PER_CELL;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			draw_pixel(&(data)->minimap, x, y, convert_color(220, 220, 220));
			draw_pixel(&(data)->minimap, y, x, convert_color(220, 220, 220));
			x++;
		}
		y += PIXELS_PER_CELL;
	}
}

void	draw_player(t_data *data)
{
	float	px;
	float	py;
	int		i;
	int		j;

	px = (data->player.x * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	py = (data->player.y * PIXELS_PER_CELL) - (SIZE_PIXEL_PLAYER / 2);
	j = 0;
	while (j < SIZE_PIXEL_PLAYER)
	{
		i = 0;
		while (i < SIZE_PIXEL_PLAYER)
		{
			draw_pixel(&(data)->minimap, (int)px + i, (int)py + j, convert_color(255, 255, 0));
			i++;
		}
		j++;
	}
	draw_player_orientation(data, (cos(data->player.angle) * LINE_LENGTH), (-sin(data->player.angle) * LINE_LENGTH));
}

void	draw_player_orientation(t_data *data, float dx, float dy)
{
	//float	dx;
	//float	dy;
	int		steps;
	float	x_increment;
	float	y_increment;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_increment = dx / steps;
	y_increment = dy / steps;
	draw_line(data, x_increment, y_increment, steps);
}

void	draw_line(t_data *data, float x_increment, float y_increment, int steps)
{
	float	x;
	float	y;
	int		i;

	x = data->player.x * PIXELS_PER_CELL;
	y = data->player.y * PIXELS_PER_CELL;
	i = 0;
	while (i < steps)
	{
		if ((int)x >= 0 && (int)x < MINIMAP_WIDTH && (int)y >= 0 && (int)y < MINIMAP_HEIGHT)
			draw_pixel(&(data)->minimap, (int)x, (int)y, convert_color(255, 255, 0));
		
		x += x_increment;
		y += y_increment;
		i++;
	}
}

void	draw_rays(t_data *data)
{
	int		r;
	int		dof;
	float	px;
	float	py;
	float	xo;
	float	yo;
	t_ray	ray;

	ray.x = 0;
	ray.y = 0;
	xo = 0;
	yo = 0;
	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray.angle = data->player.angle;
	r = 0;
	while (r < 1)
	{
		// ---Check Horizontal Lines---
		dof = 0;
		if (ray.angle == 0 || ray.angle == PI) // Looking straight left or right
		{
			ray.x = px;
			ray.y = py;
			dof = 8;
		}
		else if (ray.angle > PI) // Looking up
		{
			ray.y = floor(py / PIXELS_PER_CELL) * PIXELS_PER_CELL - 0.0001;
			ray.x = (py - ray.y) * (-1 / tan(ray.angle)) + px;
			yo = - PIXELS_PER_CELL;
			xo = - yo * (-1 / tan(ray.angle));
		}
		else if (ray.angle < PI) // Looking down
		{
			ray.y = floor(py / PIXELS_PER_CELL) * PIXELS_PER_CELL + PIXELS_PER_CELL;
			ray.x = (py - ray.y) * (-1 / tan(ray.angle)) + px;
			yo = PIXELS_PER_CELL;
			xo = - yo * (-1 / tan(ray.angle));
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
	draw_player_orientation(data, ray.x - px, ray.y - py);
}
