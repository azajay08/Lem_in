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
	printf("HOW MANY PATHS WE HAVE: %i \n", counter);
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
	printf("calc diff: %i!\n", diff);
	return (diff);
}

int	calculate_min_for_path(t_option *option, int nb_paths)
{
	t_option	*temp;
	int			big_edge;
	int			res;

	printf("\n\t CALCULATE min for path\n");
	res = 1;
	temp = option;
	while (temp->next && --nb_paths)
		temp = temp->next;
	big_edge = temp->p_len + 1;
	while (temp->previous)
	{
		printf("\t\tBIG_EDGE : %i!!\n", big_edge);
		temp = temp->previous;
		res += (big_edge - temp->p_len);
	}
	printf("res: %i\n", res);
	printf("\ncalc min for path DONE\n");
	return (res);
}

int	calculate_paths_used(t_data *data, t_option *option)
{
//	int	diff1;
//	int	diff2;
	int	nb_of_paths;

	nb_of_paths = calculate_paths(option);
	printf("\ncalc_paths_used\n");
	if (nb_of_paths < 2)
	{
		printf("\ncheckk, nb of paths: %i\n", nb_of_paths);
		return (nb_of_paths);
	}
	if ((nb_of_paths == 2 && data->nb_ants < calculate_diff(option))
		|| data->nb_ants < nb_of_paths)
	{
		printf("CALC PATHS USED == 2\n");
		return (1);
	}
	if (data->nb_ants >= calculate_min_for_path(option, nb_of_paths))
	{
		printf("CALC PATHS USED >= 2\n");
		return (nb_of_paths);
	}
	else
	{
		printf("CALT PATHS USED: RETURNING NB_OF_PATHS - 1\n");
		return (nb_of_paths - 1);
	}
	return (0);
}

void	deploy_first_round(t_option *option, int ants, int nb_paths)
{
	t_option	*opt;
	int			big_edge;

	printf("\t\tANTS: %i\n\n", ants);
	opt = option;
	while (opt->next)
		opt = opt->next;
	opt->limit = 1;
	big_edge = opt->p_len + 1;
	while (opt && nb_paths > 0)
	{
		opt = opt->previous;
		printf("\nfirst_round opt limit before: %i\t", opt->limit);
		opt->limit = big_edge - opt->p_len;
		printf("first round opt limit After: %i\t\n", opt->limit);
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

	printf("calculate ants in pants\n");
	data->nb_paths = calculate_paths(option);
	opt = option;
	if (data->nb_paths > 1)
	{
		while (opt->next)
			opt = opt->next;
		deploy_first_round(option, data->nb_ants / data->nb_paths, data->nb_paths);
		remain = data->nb_ants - calculate_min_for_path(opt, data->nb_paths);
		printf("remain: %i\n", remain);
		opt = option;
		while(opt)
		{
			opt->limit += remain / data->nb_paths;
			printf("\topt->limit in loop: %i\n", opt->limit);
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
	opt = option;
	while (opt)
	{
		printf("\t Okay: option->limit: %i\n", opt->limit);
		printf("\t Okay: option->p_len: %i\n", opt->p_len);
		opt = opt->next;
	}
}
