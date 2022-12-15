/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:23:35 by ajones            #+#    #+#             */
/*   Updated: 2022/12/13 03:20:34 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_data *data, t_opt *option)
{
	t_path		*path;
	int			i;
	int			ants;

	i = 0;
	ants = 0;
	while (option)
	{
		i++;
		ft_printf("\nPath %i:", i);
		path = get_path_head(option->path);
		path = path->next;
		ants = option->ants;
		while (path)
		{
			if (path->next == NULL)
				ft_printf(" %s - %i ants", data->room[path->index]->name, ants);
			else
				ft_printf(" %s >", data->room[path->index]->name);
			path = path->next;
		}
		option = option->next;
	}
}

void	print_flag_modes(t_data *data, t_opt *option)
{
	if (data->t_mode == ON)
		ft_printf("\nTurns: %i\n", data->turns);
	if (data->p_mode == ON)
	{
		ft_printf("\nPaths used:\n");
		print_paths(data, option);
		write(1, "\n", 1);
	}
}
