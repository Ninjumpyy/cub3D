/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_free_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:45:09 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 14:15:48 by rpandipe         ###   ########.fr       */
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
		printf("destroyed image\n");
		free(current);
		current = NULL;
		current = next;
		printf("here\n");
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
