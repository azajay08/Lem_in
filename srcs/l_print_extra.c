/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:23:35 by ajones            #+#    #+#             */
/*   Updated: 2022/12/08 02:40:44 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_data *data, t_option *option)
{
	t_path		*path;
	t_option	*opt;
	int			i;

	i = 0;
	option = get_option_head(option);
	ft_printf("Paths used:\n");
	while (opt)
	{
		i++;
		ft_printf("\nPath %i:", i);
		path = get_path_head(opt->path);
		while (path)
		{
			if (path->next == NULL)
				ft_printf(" %s", data->room[path->index]->name);
			else
				ft_printf(" %s >", data->room[path->index]->name);
			path = path->next;
		}
		opt = opt->next;
	}
	write(1, "\n", 1);
}
