/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ants.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:39:24 by ajones            #+#    #+#             */
/*   Updated: 2022/12/09 03:17:28 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_ant	*make_ant(t_data *data, t_option *opt)
{
	t_ant	*new_ant;

	data->ant_num++;
	new_ant = (t_ant *)malloc(sizeof(t_ant));
	if (!new_ant)
	{
		free_ants(data);
		free_all(data, ERROR);
		error_exit(ANTS_FAIL);
	}
	init_ant(new_ant);
	new_ant->ant_num = data->ant_num;
	new_ant->head = get_path_head(opt->path);
	return (new_ant);
}

void	reduce_paths(t_data *data, t_option *opt)
{
	opt->limit--;
	opt->used++;
	opt->ants++;
	if (opt->limit == 0)
	{
		opt->limit = REACHED;
		data->nb_paths--;
	}
}

t_ant	*crown_queen(t_data *data, t_option *opt, t_ant *ant)
{
	t_ant		*new_ant;

	new_ant = make_ant(data, opt);
	if (!data->queen)
	{
		data->queen = new_ant;
		ant = new_ant;
	}
	else
	{
		ant->next = new_ant;
		ant = ant->next;
	}
	return (ant);
}

void	make_ant_army(t_data *data, t_option *option)
{
	t_ant		*ant;
	t_option	*head;

	ant = NULL;
	head = option;
	while (data->nb_paths)
	{
		if (option->limit > 0)
		{
			reduce_paths(data, option);
			ant = crown_queen(data, option, ant);
		}
		option = option->next;
		if (!option)
			option = head;
	}
}
