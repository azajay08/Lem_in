/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/09 03:21:19 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_option	*make_t_option(t_data *data, t_path *cur_path)
{
	t_option	*new_option;

	new_option = (t_option *)malloc(sizeof(t_option));
	if (!new_option)
		error_exit1("malloc failed in t_option", data);
	new_option->next = NULL;
	new_option->previous = NULL;
	new_option->path = cur_path;
	new_option->p_len = cur_path->edges;
	new_option->limit = 0;
	new_option->ants = 0;
	new_option->used = 0;
	return (new_option);
}

t_option	*find_all_disjoint_paths(t_data *data, t_room **room)
{
	t_path		*cur_path;
	t_option	*option;

	option = NULL;
	while (1)
	{
		cur_path = bfs(data, room);
		if (cur_path == NULL)
			break ;
		if (option == NULL)
			option = make_t_option(data, cur_path);
		else
		{
			option->next = make_t_option(data, cur_path);
			option->next->previous = option;
			option = option->next;
		}
		make_residual_path(option, room);
		free (cur_path);
	}
	if (option == NULL)
		(error_exit1("no paths found\n", data));
	while (option->previous != NULL)
		option = option->previous;
	return (option);
}

t_option	*solver(t_data *data)
{
	t_option	*orig_option;
	t_option	*next_added;
	t_room		**room;

	room = make_room_array(data);
	data->room = room;
	free_vert(data);
	orig_option = find_all_disjoint_paths(data, room);
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option)
		|| calculate_paths(orig_option) <= data->nb_ants)
		return (orig_option);
	next_added = vertex_disjoint(data, room, orig_option);
	while (calculate_paths(orig_option) < calculate_paths_used(data, next_added))
	{
		free_option(orig_option);
		orig_option = next_added;
		//free_option(next_added);
		next_added = vertex_disjoint(data, room, orig_option);
	}
	free_option(next_added);
	calculate_ants_in_paths(data, orig_option);
	// all freeing are uncertain still!
	return (orig_option);
}

/*
	solver takes care of everything that happens between parsing and printing.
	
	The first if is to check if there's just one ant - in which case we don't
	need to do all the algorithms.
	The second if is a similiar check - it checks whether we have already found
	more paths than we even need.
*/
