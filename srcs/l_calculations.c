/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_calculations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:46:31 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 15:47:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	calculate_paths(t_option *option)
{
	int	counter;

	if (!option)
		return (0);
	counter = 1;
	while (option->next)
		option = option->next;
	while (option->previous)
	{
		option = option->previous;
		counter++;
	}
	return (counter);
}

int	calculate_diff(t_option *option)
{
	int			diff;
	t_option	*temp;

	temp = option->previous;
	diff = option->edges - temp->edges;
	// free (temp); // Not sure if it's a leak or not.. //
	return (diff);
}

int	calculate_min_for_path(t_option *option, int nb_paths)
{
	t_option	*temp;
	int			big_edge;
	int			res;

	res = 1;
	temp = option;
	while (temp->next && --nb_paths)
		temp = temp->next;
	big_edge = temp->edges;
	while (temp->previous)
	{
		temp = temp->previous;
		res += (big_edge - temp->edges);
	}
	return (res);
}

int	calculate_paths_used(t_data *data, t_option *option)
{
//	int	diff1;
//	int	diff2;
	int	nb_of_paths;

	nb_of_paths = calculate_paths(option);
	if (nb_of_paths < 2)
		return (nb_of_paths);
	if (nb_of_paths == 2 && data->nb_ants < calculate_diff(option))
		return (1);
	if (data->nb_ants >= calculate_min_for_path(option, nb_of_paths))
		return (nb_of_paths);
	return (0);
}

/*else if (option->next && nb_of_paths == 3)
	{
		while (option->next)
			option = option->next;
		while (1)
		{
			diff2 = calculate_diff(option);
			option = option->previous;
			diff1 = calculate_diff(option);
			if (diff2 == 0)
				diff2 = -2;
			if (data->nb_ants >= (diff1 + 3) + (diff2 * 2))
				break ; // Not sure yet if this works for all possibilities.
			nb_of_paths--;
		}
	}
	The "data->nb_ants >= (diff1 + 3) + (diff2 + 2)" works on 3 paths, but 
	not sure if it works with more. We'll see later on.///
*/


void	deploy_ants(t_option *option, int nb_paths, int added, int edges)
{
	t_option	*opt;

	opt = option;
	while (opt->next && nb_paths > 0)
	{
		opt->ants += (edges - opt->edges) * added;
		opt = opt->next;
	}
}

void	calculate_ants_in_paths(t_data *data, t_option *option)
{
	t_option	*opt;
	int			nb_paths;
	int			min_ants;
	int			remain;

	nb_paths = calculate_paths(option);
	opt = option;
	while (opt->next)
		opt = opt->next;
	remain = data->nb_ants;
	while (nb_paths > 0 && remain > 0)
	{
		min_ants = calculate_min_for_path(option, nb_paths);
		opt->ants += remain / min_ants;
		if(opt->previous && nb_paths > 1)
		{
			deploy_ants(option, nb_paths, remain / min_ants, opt->edges + 1);
			remain = remain % min_ants;
			opt = opt->previous;
		}
		nb_paths--;
	}
}
