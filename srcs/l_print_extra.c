/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 03:23:35 by ajones            #+#    #+#             */
/*   Updated: 2022/12/08 20:38:39 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_data *data, t_option *option)
{
	t_path		*path;
	int			i;
	int			ants;

	i = 0;
	ants = 0;
	ft_printf("Paths used:\n");
	while (option)
	{
		i++;
		ft_printf("\nPath %i:", i);
		path = get_path_head(option->path);
		ants = option->limit + 1;
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
