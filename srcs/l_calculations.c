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

	temp = NULL;
	while (option->next)
		option = option->next;
	if (option->previous)
	{
		temp = option->previous;
		diff = option->p_len - temp->p_len;
	}
	else
		diff = option->p_len;
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
	big_edge = temp->p_len + 1;
	while (temp->previous)
	{
		temp = temp->previous;
		res += (big_edge - temp->p_len);
	}
	return (res);
}

int	calculate_paths_used(t_data *data, t_option *option)
{
	int	nb_of_paths;

	nb_of_paths = calculate_paths(option);
	if (nb_of_paths < 2)
		return (nb_of_paths);
	if ((nb_of_paths == 2 && data->nb_ants < calculate_diff(option))
		|| data->nb_ants < nb_of_paths)
		return (1);
	if (data->nb_ants >= calculate_min_for_path(option, nb_of_paths))
		return (nb_of_paths);
	else
		return (nb_of_paths - 1);
	return (0);
}

void	deploy_first_round(t_option *option, int nb_paths)
{
	t_option	*opt;
	int			big_edge;

	opt = option;
	while (opt->next)
		opt = opt->next;
	opt->limit = 1;
	big_edge = opt->p_len + 1;
	while (opt && nb_paths > 0)
	{
		opt = opt->previous;
		opt->limit = big_edge - opt->p_len;
		nb_paths--;
		if (!opt->previous)
			break ;
	}
	opt = NULL;
}

void	calculate_ants_in_paths(t_data *data, t_option *option)
{
	t_option	*opt;
	int			remain;

	data->nb_paths = calculate_paths(option);
	opt = option;
	if (data->nb_paths > 1)
	{
		while (opt->next)
			opt = opt->next;
		deploy_first_round(option, data->nb_paths);
		remain = data->nb_ants - calculate_min_for_path(opt, data->nb_paths);
		opt = option;
		while (opt)
		{
			opt->limit += remain / data->nb_paths;
			opt = opt->next;
		}
		remain = remain % data->nb_paths;
		opt = option;
		while (remain--)
		{
			opt->limit++;
			opt = opt->next;
		}
	}
	else
		opt->limit = data->nb_ants;
}
