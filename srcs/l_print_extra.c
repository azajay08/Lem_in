/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:23:35 by ajones            #+#    #+#             */
/*   Updated: 2022/12/18 03:22:48 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_data *data, t_opt *opt)
{
	t_path		*path;
	int			i;

	i = 0;
	while (opt)
	{
		i++;
		ft_printf("\nPath %i:", i);
		path = get_path_head(opt->path);
		path = path->next;
		while (path)
		{
			if (path->next == NULL)
			{
				ft_printf(" %s | ", data->room[path->index]->name);
				ft_printf("Path length: %i | Ants: %i", opt->p_len, opt->ants);
			}
			else
				ft_printf(" %s >", data->room[path->index]->name);
			path = path->next;
		}
		opt = opt->next;
	}
}

void	print_flag_modes(t_data *data, t_opt *opt, int paths)
{
	if (data->t_mode == ON)
		ft_printf("\nTurns: %i\n", data->turns);
	if (data->p_mode == ON)
	{
		ft_printf("\nPaths used: %i\n", paths);
		print_paths(data, opt);
		write(1, "\n", 1);
	}
}
