/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_wall_slice.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:46:43 by thomas            #+#    #+#             */
/*   Updated: 2024/10/28 11:56:47 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_wall_slice(t_data *data, t_ray ray, int r)
{
	float			wall_height;
	int				y;
	int				y_end;
	int				color;
	t_texture_info	tex_info;

	wall_height = (TILE_SIZE * CUB_HEIGHT)
		/ (ray.dist * cos(data->player.angle - ray.angle));
	calculate_texture_x_coordinate(data, &ray, &tex_info);
	calculate_texture_scaling(&tex_info, &wall_height, ray);
	determine_wall_slice_bounds(&y, &y_end, wall_height);
	while (y < y_end)
	{
		tex_info.tex_y = (int)tex_info.tex_pos % ray.texture.height;
		tex_info.tex_pos += tex_info.tex_step;
		color = get_texture_color(&ray.texture, tex_info.tex_x, tex_info.tex_y);
		draw_pixel(&(data)->cub, r, y, color);
		y++;
	}
}

void	calculate_texture_x_coordinate(t_data *data, t_ray *ray,
t_texture_info *tex_info)
{
	float	wall_hit_x;

	(void)data;
	if (ray->type == VERTICAL)
		wall_hit_x = ray->y - (int)ray->y;
	else
		wall_hit_x = ray->x - (int)ray->x;
	if (ray->open_amount != -1.0)
	{
		wall_hit_x += ray->open_amount;
	}
	tex_info->tex_x = (int)(wall_hit_x * ray->texture.width);
}

void	calculate_texture_scaling(t_texture_info *tex_info,
float *wall_height, t_ray ray)
{
	tex_info->tex_step = (float)ray.texture.height / *wall_height;
	if (*wall_height > CUB_HEIGHT)
	{
		tex_info->tex_pos = (*wall_height
				- CUB_HEIGHT) / 2 * tex_info->tex_step;
		*wall_height = CUB_HEIGHT;
	}
	else
		tex_info->tex_pos = 0;
}

void	determine_wall_slice_bounds(int *y, int *y_end, float wall_height)
{
	*y = (CUB_HEIGHT - wall_height) / 2;
	*y_end = *y + wall_height;
	if (*y_end > CUB_HEIGHT)
		*y_end = CUB_HEIGHT;
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (y * texture->line_size + x
			* (texture->bits_per_pixel / 8));
	color = *(int *)pixel;
	return (color);
}
