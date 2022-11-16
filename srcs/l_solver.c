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

int	calculate_paths(t_option *option)
{
	int	counter;

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

int	calculate_paths_used(t_data *data, t_option *option)
{
	int	diff1;
	int	diff2;
	int	nb_of_paths;

	nb_of_paths = calculate_paths(option);
	if (option->next)
	{
		while (option->next)
			option = option->next;
		while(1)
		{
			diff2 = calculate_diff(option);
			option = option->previous;
			diff1 = calculate_diff(option);
			if (diff2 == 0)
				diff2 = -2;
			if (data->nb_ants >= (diff1 + 3) + (diff2 + 2))
				break ;
			nb_of_paths--;
		}
	}
	return (nb_of_paths);
}

/*
	The "data->nb_ants >= (diff1 + 3) + (diff2 + 2)" works on 3 paths, but 
	not sure if it works with more. We'll see later on.///
*/

int	send_ants(t_data *data, t_option *option)
{
	int	paths;

	paths = calculate_paths(option);

}

t_option	*find_all_disjoint_paths(t_data *data)
{
	t_path		*cur_path;
	t_option	*all_paths;

	all_paths = NULL;
	while (1)
	{
		cur_path = bfs(data);
		if (cur_path == NULL)
			break ;
		if (all_paths->start == NULL)
			all_paths = make_t_option(data, cur_path);
		else
		{
			all_paths->next = make_t_option(data, cur_path);
			all_paths->next->previous = all_paths;
			all_paths = all_paths->next;
		}
		free (cur_path);
	}
	if (all_paths == NULL)
		(error_exit1("no paths found\n", data));
	while (all_paths->previous != NULL)
		all_paths = all_paths->previous;
	return (all_paths);
}

void	solver(t_data *data)
{
	t_option	*orig_option;
	t_option	*next_added;

	if (data->nb_ants == 1)
		return (bfs(data));//Just to show that it skips all funcitons after bfs.
	orig_option = find_all_disjoint_paths(data);
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option))
		return (orig_option);
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
