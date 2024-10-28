/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:47:49 by tle-moel          #+#    #+#             */
/*   Updated: 2024/10/28 11:54:12 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	hit_ray_logic(t_data *data, t_ray *ray)
{
	ray->dof = DOF_MAX;
	if (ray->x < 0)
		ray->x = 0;
	if (ray->x >= data->map_width)
		ray->x = data->map_width - 1;
	if (ray->y < 0)
		ray->y = 0;
	if (ray->y >= data->map_height)
		ray->y = data->map_height - 1;
}
