/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/20 14:02:51 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_opt	*make_t_opt(t_data *data, t_path *cur_path)
{
	t_opt	*new_option;

	new_option = (t_opt *)malloc(sizeof(t_opt));
	if (!new_option)
		error_exit1(OPT_FAIL, data);
	new_option->next = NULL;
	new_option->previous = NULL;
	new_option->path = cur_path;
	new_option->p_len = cur_path->edges;
	new_option->limit = 0;
	new_option->ants = 0;
	new_option->used = 0;
	return (new_option);
}

int	calculate_paths(t_opt *option)
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

t_opt	*cut_paths(t_data *data, t_opt *option)
{
	t_opt		*temp;
	int			used;
	int			i;

	i = 0;
	used = calculate_paths_used(data, option);
	temp = option;
	while (i++ < used && temp->next)
		temp = temp->next;
	if (temp && i > 1)
	{
		temp->previous->next = NULL;
		free_path(temp->path);
		free(temp);
	}
	calculate_ants_in_paths(data, option);
	return (option);
}

t_opt	*find_all_disjoint_paths(t_data *data, t_room **room)
{
	t_path		*cur_path;
	t_opt		*option;

	option = NULL;
	while (1)
	{
		cur_path = bfs(data, room);
		if (cur_path == NULL)
			break ;
		if (option == NULL)
			option = make_t_opt(data, cur_path);
		else
		{
			option->next = make_t_opt(data, cur_path);
			option->next->previous = option;
			option = option->next;
		}
		if (data->nb_ants < calculate_min_for_path(option))
			break ;
		make_residual_path(option, room, OFF);
	}
	if (option == NULL)
		(error_exit1(NO_PATHS, data));
	option = get_opt_head(option);
	return (option);
}

t_opt	*solver(t_data *data, t_room **room)
{
	t_opt		*orig_option;
	t_opt		*next_opt;

	orig_option = find_all_disjoint_paths(data, room);
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option))
	{
		// printf("check 1\n");
		orig_option = cut_paths(data, orig_option);
	}
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option)
		|| calculate_paths(orig_option) >= data->nb_ants)
		return (cut_paths(data, orig_option));
	// printf("check 2\n");
	next_opt = vertex_disjoint(data, room, orig_option);
	while (calculate_paths(orig_option) <= calculate_paths_used(data, next_opt))
	{
		// printf("check 3\n");
		free_option(orig_option);
		orig_option = next_opt;
		next_opt = vertex_disjoint(data, room, orig_option);
	}
	if (next_opt)
		free_option(next_opt);
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option))
		orig_option = cut_paths(data, orig_option);
	if (orig_option->limit == 0)
		calculate_ants_in_paths(data, orig_option);
	return (orig_option);
}

/*
	solver takes care of everything that happens between parsing and printing.
	
	The first if is to check if there's just one ant - in which case we don't
	need to do all the algorithms.
	The second if is a similiar check - it checks whether we have already found
	more paths than we even need.
*/
