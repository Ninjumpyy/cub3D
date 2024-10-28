/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:45:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 14:39:20 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_animation(t_player *ptr, t_data *data)
{
	t_sprite	*current;
	t_sprite	*next;

	current = &ptr->animation;
	mlx_destroy_image(data->mlx, current->img.img);
	current = current->next;
	while (current != NULL)
	{
		next = current->next;
		mlx_destroy_image(data->mlx, current->img.img);
		free(current);
		current = NULL;
		current = next;
	}
}

void	free_texture(char *tx)
{
	if (tx)
	{
		free(tx);
		tx = NULL;
	}
}

void	free_env(t_data *data)
{
	free_texture(data->env.no_texture);
	free_texture(data->env.so_texture);
	free_texture(data->env.ea_texture);
	free_texture(data->env.we_texture);
	free_texture(data->env.door_texture);
	if (data->env.map)
	{
		free_map(data);
		data->env.map = NULL;
	}
}
