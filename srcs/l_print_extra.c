/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_printing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:23:35 by ajones            #+#    #+#             */
/*   Updated: 2022/12/06 18:14:42 by ajones           ###   ########.fr       */
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
	write(1, "\n", 1);
	while (opt)
	{
		i++;
		ft_printf("\nPath%i:", i);
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
