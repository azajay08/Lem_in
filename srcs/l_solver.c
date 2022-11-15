/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/08 20:44:11 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_option	*make_t_option(t_data *data, t_path *cur_path)
{
	t_option	*new_option;

	new_option = (t_option *)malloc(sizeof(t_option));
	if (!new_option)
		error_exit(data);
	new_option->next = NULL;
	new_option->previous = NULL;
	new_option->start = cur_path;
	new_option->turns = 0;
	return (new_option);
}

t_option	*find_all_disjoint_paths(t_data *data)
{
	t_path		*cur_path;
	t_option	*paths;

	while (1)
	{
		cur_path = bfs(data);
		if (cur_path == NULL)
			break ;
		if (paths->start == NULL)
			paths = make_t_option(data, cur_path);
		else
		{
			paths->next = make_t_option(data, cur_path);
			paths->next->previous = paths;
			paths = paths->next;
		}
		free (cur_path);
	}
	while (paths->previous != NULL)
		paths = paths->previous;
	return (paths);
}

/*
	I think we need to make another struct that holds all the paths inside.
	Like that option -thing, like option 1 has 2 paths inside, option 2 has 3 etc...
*/

void	solver(t_data *data)
{
	t_option	*orig_option;
	t_option	*next_added;

	if (data->nb_ants == 1)
		return (bfs(data));//Just to show that it skips all funcitons after bfs.
	orig_option = find_all_disjoint_paths(data);
	if (we use less paths than found in above function)
		return (orig_option->start);
	while (orig_option->turns >= next_added->turns)
	{
		free (orig_option);
		orig_option = next_added;
		free (next_added);
		next_added = vertex_disjoint(data, orig_option);
	}
	// print here or in the main?
	// If in the main, we need to either return the string from here,
	// or save it in data.
}
