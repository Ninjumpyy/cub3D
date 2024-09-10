/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:35:48 by tle-moel          #+#    #+#             */
/*   Updated: 2024/09/10 10:35:33 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_arg(int argc, char **argv)
{
	char	*term;

	if (argc != 2)
	{
		if (write(2, "Error: wrong number of arguments\n", 33) == -1)
			exit(1);
		exit(1);
	}
	term = ft_strrchr(argv[1], '.');
	if (ft_strcmp(term, ".cub") != 0)
	{
		if (write(2, "Error: .cub file required\n", 26) == -1)
			exit(1);
		exit(1);
	}
}

int	add_node(char *line, t_lst	**lst)
{
	t_lst	*new;
	t_lst	*ptr;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		return (1);
	new->next = NULL;
	new->prev = NULL;
	new->line = line;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		new->prev = ptr;
		ptr->next = new;
	}
	return (0);
}
