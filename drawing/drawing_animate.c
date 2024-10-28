/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_animate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:50:54 by rpandipe          #+#    #+#             */
/*   Updated: 2024/10/28 14:22:02 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	allocate_sprite(t_data *data, t_sprite *ptr, int count)
{
	int			i;
	t_sprite	*sprite;

	sprite = ptr;
	i = 0;
	while (i < count)
	{
		sprite->next = malloc(sizeof(t_sprite));
		if (!sprite->next)
		{
			ft_error("Error\nMemory Allocation Failed\n");
			free_cub3d(data);
			exit(EXIT_FAILURE);
		}
		sprite = sprite->next;
		sprite->next = NULL;
		i++;
	}
}

void	load_image(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path, \
									&img->width, &img->height);
	if (!img->img)
	{
		ft_error("Error loading player assets\n");
		free_cub3d(data);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
									&img->line_size, &img->endian);
	if (!img->addr)
	{
		ft_error("Error loading player assets\n");
		free_cub3d(data);
		exit(EXIT_FAILURE);
	}
}

void	load_animation(t_data *data)
{
	t_sprite	*ptr;

	ptr = &data->player.animation;
	allocate_sprite(data, ptr, 9);
	load_image(data, &ptr->img, "./textures/weapon/Idle.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing1.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing2.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing3.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing4.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing5.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing6.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing7.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing8.xpm");
	ptr = ptr->next;
	load_image(data, &ptr->img, "./textures/weapon/Firing9.xpm");
	data->player.sprite = data->player.animation;
	data->player.current_sprite = data->player.animation;
}

void	play_animation(t_data *data, t_sprite *sprite)
{
	double		current_time;
	double		diff;

	current_time = get_time();
	diff = current_time - data->animation_time;
	if (diff > 0.05)
	{
		if (sprite->next)
			data->player.current_sprite = *sprite->next;
		else
		{
			data->player.current_sprite = data->player.animation;
			data->key.mouse_left = 0;
		}
		data->animation_time = get_time();
	}
	data->player.sprite = data->player.current_sprite;
}
