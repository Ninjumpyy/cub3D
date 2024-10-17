/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:26 by thomas            #+#    #+#             */
/*   Updated: 2024/10/17 15:33:30 by tle-moel         ###   ########.fr       */
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

void	cast_rays(t_data *data)
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
	float	da;

	xo = 0;
	yo = 0;
	px = data->player.x * PIXELS_PER_CELL;
	py = data->player.y * PIXELS_PER_CELL;
	ray_h.x = px;
	ray_h.y = py;
	ray_h.angle = data->player.angle - (DR * 30);
	da = (DR * 60) / CUB_WIDTH;
	if (ray_h.angle < 0)
		ray_h.angle += (2 * PI);
	if (ray_h.angle > 2 * PI)
		ray_h.angle -= (2 * PI);
	ray_v.angle = ray_h.angle;
	r = 0;
	while (r < CUB_WIDTH)
	{
		cotan = 1 / tan(ray_h.angle);
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
		if (dist_v < dist_h)
		{
			draw_line(data, (int)ray_v.x, (int)ray_v.y, convert_color(0, 128, 0));
			draw_cub(data, dist_v, r, ray_v, 1);
		}
		else
		{
			draw_line(data, (int)ray_h.x, (int)ray_h.y, convert_color(0, 128, 0));
			draw_cub(data, dist_h, r, ray_h, 0);
		}
		r++;
		ray_h.angle += da;
		if (ray_h.angle < 0)
			ray_h.angle += (2 * PI);
		if (ray_h.angle > 2 * PI)
			ray_h.angle -= (2 * PI);
		ray_v.angle = ray_h.angle;
	}
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	max_height;

	max_height = CUB_HEIGHT / 2;
	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < CUB_WIDTH)
		{
			draw_pixel(&(data)->cub, x, y, convert_color(data->env.ceiling.r, data->env.ceiling.g, data->env.ceiling.b));
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	y = CUB_HEIGHT / 2;
	while (y < CUB_HEIGHT)
	{
		x = 0;
		while (x < CUB_WIDTH)
		{
			draw_pixel(&(data)->cub, x, y, convert_color(data->env.floor.r, data->env.floor.g, data->env.floor.b));
			x++;
		}
		y++;
	}
}

void	draw_cub(t_data *data, float dist, int r, t_ray ray, int vertical)
{
	float	line_height;
	int		y_start;
	int		y_end;
	int		y;
	float	wall_hit_x;
	int		tex_x;
	int		tex_y;
	float	tex_pos;
	float	tex_step;
	int		color;

	line_height = (TILE_SIZE * CUB_HEIGHT) / (dist * cos(data->player.angle - ray.angle));
	tex_step = (float)data->texture.north.height / line_height;
	if (line_height > CUB_HEIGHT)
	{
		tex_pos = (line_height - CUB_HEIGHT) / 2 * tex_step;
		line_height = CUB_HEIGHT;
	}
	else
		tex_pos = 0;
	
	y_start = (CUB_HEIGHT - line_height) / 2;
	if (y_start < 0)
    {
        tex_pos += -y_start * tex_step;
        y_start = 0;
    }
	y_end = y_start + line_height;
	if (y_end > CUB_HEIGHT)
		y_end = CUB_HEIGHT;

	if (vertical)
	{
		ray.y /= 32;
		wall_hit_x = ray.y - (int)ray.y;
	}
	else
	{
		ray.x /= 32;
		wall_hit_x = ray.x - (int)ray.x;
	}

	tex_x = (int)(wall_hit_x * data->texture.north.width);
	
	y = y_start;
	while (y < y_end)
	{
		tex_y = (int)tex_pos % data->texture.north.height;
		tex_pos += tex_step;

		color = get_texture_color(&data->texture.north, tex_x, tex_y);
		draw_pixel(&(data)->cub, r, y, color);
		y++;
	}
}


int get_texture_color(t_text *texture, int x, int y)
{
    char    *pixel;
    int     color;

    pixel = texture->addr + (y * texture->line_size + x * (texture->bits_per_pixel / 8));
    color = *(int *)pixel;
    return (color);
}

